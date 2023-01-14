/* KeyPressable.hpp
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

#ifndef BWIDGETS_KEYPRESSABLE_HPP_
#define BWIDGETS_KEYPRESSABLE_HPP_

#include "Callback.hpp"
#include "Support.hpp"

namespace BWidgets
{

/**
 *  @brief  Supports keyboard key press and release events.
 */
class KeyPressable : virtual public Callback, public Support
{
public:

    /**
     *  @brief  Switch the support for key press and release events on/off.
     *  @param status  True if on, otherwise false.
     *
     *  Defines whether a widget may emit a KeyEvent if the main window event 
     *  handler received a key event from the host. In this case, a KeyEvent 
     *  with the type keyPressEvent or keyReleaseEvent will be scheduled 
     *  and send to the widget.
     */
    virtual void setKeyPressable (const bool status) {setSupport (status);}

    /**
     *  @brief  Information about the support for key press and release events.
     *  @return  True if on, otherwise false.
     *
     *  If a widget is keyPressable, the main window event handler let the 
     *  widget emit a KeyEvent if a keyboard key is pressed or released.
     */
    bool isKeyPressable () const {return getSupport();}

    /**
     *  @brief  Method when a KeyEvent with the type keyPressEvent is 
     *  received.
     *  @param event  Passed Event.
     *
     *  Overridable method called from the main window event scheduler if a
     *  key is pressed. By default, it calls its static callback function.
     */
    virtual void onKeyPressed (BEvents::Event* event)
    {
        callback (BEvents::Event::EventType::valueChangedEvent) (event);
    }

    /**
     *  @brief  Method when a KeyEvent with the type keyReleaseEvent is 
     *  received.
     *  @param event  Passed Event.
     *
     *  Overridable method called from the main window event scheduler if a
     *  key is released. By default, it calls its static callback function.
     */
    virtual void onKeyReleased (BEvents::Event* event)
    {
        callback (BEvents::Event::EventType::valueChangedEvent) (event);
    }

};

}
#endif /* BWIDGETS_KEYPRESSABLE_HPP_ */