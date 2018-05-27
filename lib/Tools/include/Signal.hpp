/** @file include/Signal.hpp Signal.hpp
  * @brief provides a @em Signal @em Slot @em system implementation
  *
  * @author Philippe Dunski <dunski.philippe@gmail.com>
  * @version 1.0
  * @todo have a better dealing with threads
  * @copyright MIT License
  */
// Copyright 2018 Philippe Dunski <dunski.philippe@gmail.com>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy 
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is furnished
// to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in 
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
// WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR
// IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
#ifndef TOOLS_SIGNAL_HPP_INCLUDED
#define TOOLS_SIGNAL_HPP_INCLUDED
#include <map>
#include <functional>
#include <memory>
#include <cassert>
/** @ingroup Tools{
  */
namespace Tools{
template <typename ... Args>
class Signal;
class Connection;
/** @internal{
  */
/** @ingroup ToolsDetails{
  *
  */
namespace Details{
class Link;
/** @internal
  * @brief Public interface for all signals
  *
  * Provides the common public interface used by the @em duck @em typing concept
  *
  */
class SignalBase{
public:
    SignalBase(){}
    SignalBase(SignalBase const &)= delete;
    SignalBase& operator=(SignalBase const &) = delete;
    virtual ~SignalBase() = default;
    /** @brief allows to know if the signal himself is blocked
      *
      * @return @c true if the signal is blocked, @c false otherwhise
      *
      * @note if blocked() returns true, it means that none of the connected slots
      * will be called until unblock() function il called, no matters how many
      * times the underlying signal may be emitted
      *
      * @warning when blocked() returns @c false, it means that connected slots
      * @b may be called, but only those which aren't specifiquely blocked will 
      * be
      *
      * @sa void Link::blocked()
      */
    bool blocked() const{
        return blocked_;
    }
    /** @brief blocks the underlying signal to avoid call of its slots
      *
      * @note if block() is called once it does that none of the connected slots
      * will be called until unblock() function il called, no matters how many
      * times the underlying signal may be emitted
      */
    void block() const{
        blocked_=true;
    }
    /** @brief unblocks the underlying signal to allow it to call its slots
      *
      */
    void unblock() const{
        blocked_=false;
    }
    virtual void disconnect(size_t id) const{
    }
    virtual std::unique_ptr<Link> copy(size_t id) const =0;
private:
    mutable bool blocked_{false};
};
/** @internal
  * @brief @em duck @em typed signal implementation
  *
  * @tparam ... Args parameter types list used for slots
  *
  */
template <typename ... Args>
class ConcreteSignal : public SignalBase{
    /* @internal
     * @brief internal representation of links between signal and connected slots
     *
     */
    struct LinkInfo{
        /** @internal
          * @brief an easy representation way for a reference to related link
          *
          */
        using conn_ref = std::reference_wrapper<Link>;
        /** @internal
          * @brief an easy representation way for connected slot
          */
        using slot_type = std::function<void(Args...)>;
        LinkInfo(Link & conn, slot_type slot):
                connection{conn}, slot{slot}{
        }
        /** @internal
          * @brief reference to te link between current signal and connected slot
          */
        conn_ref connection;
        /** @internal
          * @internal the slot to be called 
          */
        slot_type slot;
    };
public:
    /** @internal
      * @brief easy way to represent a pointer to the link concept
      *
      */
    using conn_ptr =std::unique_ptr<Link>;
    /** @internal
      * @brief easy way to represent the slot concept
      *
      */
    using slot_type = std::function<void(Args ...)>;
    ~ConcreteSignal(){
        for(auto it : slots_){
            it.second.connection.get().signalDead();
        }
    }
    /** @internal 
      * @brief adds the given slot to the slots list to be called
      *
      * @param[in] slot the slot to be connected
      * @param[in] blocked the slot starting @em blocked @em state (defaults to false)
      * @return a pointer to the created link
      *
      */
    conn_ptr connect(slot_type slot, bool blocked = false) const{
        ++nextId_;
        auto conn=std::make_unique<Link>(
        const_cast<ConcreteSignal *>(this),nextId_, blocked);
        slots_.insert(std::make_pair(nextId_, LinkInfo(*conn.get(),slot)));
        return conn;
    }
    /** @internal
      * @brief calls all (non blocked) slots links
      *
      * @param[in] args parameters to pass to all slot when calling them
      *
      * @note slots will be called only if blocked() == false
      *
      */ 
    void operator()(Args ... args) const {
        if(!blocked()){
            for(auto const & it : slots_){
                if(! it.second.connection.get().blocked())
                    it.second.slot(args...);
            }
        }
    }
    /** @internal 
      * @brief disconnect a slot
      *
      * destroy and remove a link of the links list to be called
      * @param[in] id the link id to be removed
      *
      */
    void disconnect(size_t id) const final override{
        auto result =slots_.erase(id);
        assert(result == 1);
    }
    /** @brief create a copy of a providen signal
      *
      * @param[in] id link's id to be copyed
      * @return pointer to the newly (copied) created link
      *
      * @note as far as copied link is not removed from the links list, using 
      * this function alone can produce multiple calls to an unique slot
      */
    conn_ptr copy(size_t id) const  final override{
        auto it = slots_.find(id);
        assert(it !=slots_.end());
        return connect(it->second.slot, it->second.connection.get().blocked());
    }
private:
    mutable std::map<size_t, LinkInfo> slots_;
    mutable size_t nextId_{0};
};
/** @brief public interface used to manage the link between a signal and a specific
  * slot
  */
class Link{
public:
    Link():Link{nullptr,0}{
    }
    Link(SignalBase * sig, size_t id, bool blocked = false):
        sig_{sig},id_{id},blocked_{blocked}{
    }
    ~Link(){
        if(sig_!=nullptr)
            disconnect();
    }
    using conn_ptr = std::unique_ptr<Details::Link>;
    /** @brief allows to know if the current link correspond to an existing 
      * connection 
      *
      * @ return @c true if the link represent an existing connection between a slot
      * and a signal, @c false otherwhise
      *
      */
    bool connected() const{
        return sig_!= nullptr;
    }
    /** @brief allows to know if the current link is blocked or not
      *
      * @return @c true if current link doesn't represent an existing connection
      * @b or if the link is blocked, @c false otherwhise
      * @note if blocked() returns true, it means that specific underlying slot (if exists)
      * @b will @b not @b be @b called, no matters how many times signal could be
      * emitted until unblock() function has be called
      */
    bool blocked() const{
        return connected() && blocked_;
    }
    /** @brief block a link to avoid calling the specific underlying slot
      *
      * @warning once block() has been called for a specific link, the specific 
      * underlyingslot (if exists) @b will @b not @b be @b called  until 
      * unblock() function has be called, no matters how many times corresponding
      * signal could be emitted
      */
    void block()const{
        blocked_=true;
    }
    void unblock()const{
        blocked_=false;
    }
    /** @brief allows to create a @em deep @em copy of the current link
      *
      * As far as link has @em entity @em semantic, due to the id related to 
      * all of them, we need a specific way to correctly make a copy (with unique
      * id) of it and to correctly take it in charge in the signal.
      * 
      * This function take all the copy process in charge
      * @return a pointer to the copied link
      *
      */
    conn_ptr copy() const{
        if(sig_==nullptr)
            return conn_ptr{nullptr};
        return sig_->copy(id_);
    }
    void disconnect() const{
        assert(sig_!=nullptr);
        sig_->disconnect(id_);
        sig_=nullptr;
    }
    void signalDead() const{
        sig_=nullptr;
    }
private:
    mutable SignalBase * sig_;
    size_t id_;
    mutable bool blocked_;
};
} // namespace Details

/**@}*/
/**@}*/
/** @ingroup Signals{
  *
  */
/** @brief représente la connexion qui existe entre un signal et un slot bien
  * particulier et la maintient active
  *
  * @warning La destruction d'une connexion a pour @b effet @b immédiat de provoquer
  * la @b déconnexion @b irrémédiable du slot sous-jacent auprès du signal auquel
  * il est connecté.
  *
  * @warning vous @b devez récupérer @b systématiquement les connexion générées
  * par un signal, autrement le slot connecté ne sera pas appelé.
  *
  * @sa template <typename ... Args> Signal::connect(typename Signal<...Args>::slot_type)
  */
class Connection{
    using conn_ptr = std::unique_ptr<Details::Link>;
public:
    /** @brief default Connection ctor
      *
      * produces a connection which links with nothing
      */
    Connection():conn_{nullptr}{
    }
    /** @brief Connection ctor
      *
      * Produces a connection which links effectively a signal to a slot
      *
      */
    Connection(conn_ptr & conn):conn_{std::move(conn)}{
    }
    Connection(Connection const & other):conn_{std::move(other.copy())}{
    }
    Connection & operator=(Connection const & other){
        Connection c{other};
        swap(c);
        return *this;
    }
    /** @brief allows the user to know if the connection reflect an existing link
      * between a signal and a slot
      *
      * @return @c true if there is effectively a link, @c false otherwhise
      */
    bool connected() const{
        return conn_!=nullptr && conn_.get()->connected();
    }
    /** @brief Allows the user to know if link is blocked or not
      *
      * blocked links will ensure that related slot will not be called when
      * the signal is emited
      *
      * @return @c true if there are are not effective link or if the link is blocked,
      * @c false otherwhise
      *
      */
    bool blocked() const{
        if(!connected())
            return true;
        return conn_!=nullptr && conn_.get()->blocked();
    }
    /** @brief allows the user to block a link
      *
      * blocked links will ensure that related slot will not be called when
      * the signal is emited
      *
      */
    void block() const{
        assert(conn_!=nullptr);
        conn_.get()->block();
    }
    /** @brief allows the user to unblock a blocked link
      *
      */
    void unblock() const{
        assert(conn_!=nullptr);
        conn_.get()->unblock();
    }
    /** @brief destroy the link between a signal and a slot (if exists)
      *
      */
    void disconnect() const{
        conn_.reset();
    }
    /** @brief swaps link between current connection and another one
      *
      * @param[in,out] other the connection from which link with one to be swapped
      *
      */ 
    void swap(Connection & other){
        std::swap(conn_,other.conn_);
    }
private:
    conn_ptr copy() const{
        if(conn_!=nullptr)
            return conn_.get()->copy();
        return nullptr;
    }
    mutable conn_ptr conn_;
};
/** @brief Signal concept usable by anybody
  *
  * @tparam Args parameters required by all slots to be connected
  *
  */
template <typename ... Args>
class Signal{
    /** @internal {
      */
    /** @brief un alias de type sur la spécialisation totale du signal utilisé
      */
    using signal_type = Details::ConcreteSignal<Args...>;
    /** @brief un alias de type sur la spécialisation totale d'un pointeur sur 
      * un signal utilisé
      */
    using signal_ptr = std::unique_ptr<signal_type>;
   /** }@endinternal
     */
public:
    /** @brief un alias de type sur la signature des fonctions susceptibles d'être 
      * utilisées comme slot
      */
    using slot_type = std::function<void(Args ...) >;
    /** @brief adds a given slot to the slots lits to be called
      *
      * @param slot The slot to be called
      * @return a Tools::Connection representing the link between the signal and
      * the given slot
      *
      * @warning You @b have @b to get the resulting Tools::Connection in account
      * since its destructor will break the link between the underlying slot an
      * and the signal.
      * @warning 
      */
    Connection connect(slot_type slot){
        assert(sig_!=nullptr);
        auto temp = sig_.get()->connect(slot);
        return Connection{temp};
    }
    /** @brief calls all connected (not blocked) slots
      *
      * @param args needed parmeters to call slots
      * @pre sig.blocked() == false
      *
      * @note each slot connected will be called only if its related connection
      * is not blocked
      *
      */
    void operator()(Args ... args){
        assert(sig_!=nullptr);
        sig_.get()->operator()(args...);
    }
    /** @brief block the signal such that it will not be emited
      *
      */
    void block() const{
        assert(sig_!=nullptr);
        sig_.get()->block();
    }
    /** @brief unblock the signal if it is blocked
      *
      */ 
    void unblock() const{
        assert(sig_!=nullptr);
        sig_.get()->unblock();
    }
    /** @brief allows to know if the signal is blocked or not
      *
      * @return @c true if the signal is blocked and will not be emited, @c false
      * otherwhise
      */
    bool blocked() const{
        assert(sig_!=nullptr);
        return sig_.get()->blocked();
    }
private:
    mutable signal_ptr sig_{std::move(std::make_unique<signal_type>())};
};
} // namespace Tools
/**@}*/
/**@}*/
#endif // TOOLS_SIGNAL_HPP_INCLUDED
