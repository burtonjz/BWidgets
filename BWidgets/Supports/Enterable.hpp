/* Enterable.hpp
 * Copyright (C) 2018 - 2023  Sven Jähnichen
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef BWIDGETS_ENTERABLE_HPP_
#define BWIDGETS_ENTERABLE_HPP_

#include "Linkable.hpp"

namespace BWidgets
{

/**
 *  @brief  Interface class for Support to enter a widget.
 *
 *  %Enterable is a hint for a widget to get in a focus from a bigger
 *  context (the whole user interface). Depending on the implementation,
 *  entered widgets may get activated and/or take over keyboard control.
 */
class Enterable : public Support
{
public:

    /**
     *  @brief  Constructs a default %Enterable object with INACTIVE 
     *  support.
     */
    Enterable ();

    /**
     *  @brief  Constructs a %Enterable object with a provided support 
     *  status.
     *  @param status  Support status. 
     */
    Enterable (const bool status);

    /**
     *  @brief  Switch the support to enter a Widget on/off.
     *  @param status  True if on, otherwise false.
     */
    virtual void setEnterable (const bool status);

    /**
     *  @brief  Information about the support to enter a Widget.
     *  @return  True if on, otherwise false.
     */
    bool isEnterable () const;
    
    /**
     *  @brief  Enters this object
     *
     *  Overridable virtual method. By default, it only calls to leave all 
     *  other objects linked to the same Linkable main object to become the
     *  only entered object.
     */
    virtual void enter ();

    /**
     *  @brief  Leaves this object
     *
     *  Overridable empty virtual method.
     */
    virtual void leave ();

};

inline Enterable::Enterable () : Enterable (false) {}

inline Enterable::Enterable (const bool status) : 
    Support (status)
{}

inline void Enterable::setEnterable (const bool status)
{
    setSupport(status);
}

inline bool Enterable::isEnterable () const
{
    return getSupport();
}

inline void Enterable::enter () 
{
    // Don't do anything here

    // But leave all other widgets
    Linkable* l = dynamic_cast<Linkable*>(this);
    if (!l) return;
    Linkable* m = l->getMain();
    if (!m) return;
    m->forEachChild ([this] (Linkable* l)
    {
        Enterable* e = dynamic_cast<Enterable*>(l);
        if (e && e->isEnterable() && (e != this)) e->leave();
        return true;
    });
}

inline void Enterable::leave ()
{
    // Don't do anything here
}

}
#endif /* BWIDGETS_ENTERABLE_HPP_ */