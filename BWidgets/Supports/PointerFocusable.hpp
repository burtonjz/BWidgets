/* PointerFocusable.hpp
 * Copyright (C) 2019 - 2022  Sven Jähnichen
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

#ifndef BWIDGETS_POINTERFOCUSABLE_HPP_
#define BWIDGETS_POINTERFOCUSABLE_HPP_

#define BWIDGETS_DEFAULT_POINTERFOCUS_IN_MS 200
#define BWIDGETS_DEFAULT_POINTERFOCUS_OUT_MS 5000
#define BWIDGETS_DEFAULT_POINTERFOCUS_NAME "/focus"

#include <chrono>
#include "Callback.hpp"
#include "Support.hpp"

namespace BWidgets
{

/**
 *  @brief  Widget focus support.
 *
 *  PointerFocusable widgets may emit FocusEvents with the type POINTER_FOCUS_IN_EVENT or
 *  POINTER_FOCUS_OUT_EVENT if the pointer rests over a widget.
 */
class PointerFocusable : virtual public Callback, public Support
{
protected:
    std::chrono::milliseconds focusInMs_;
    std::chrono::milliseconds focusOutMs_;

public:

	/**
	 *  @brief  Constructs a PointerFocusable object with default parameters.
	 *
	 *  PointerFocusable objects may emit FocusEvents with the type POINTER_FOCUS_IN_EVENT
	 *  or POINTER_FOCUS_OUT_EVENT if the pointer rests over a widget. The default
	 *  time to emit POINTER_FOCUS_IN_EVENT is BWIDGETS_DEFAULT_POINTERFOCUS_IN_MS, and
	 *  the default time to emit POINTER_FOCUS_OUT_EVENT is 
	 *  BWIDGETS_DEFAULT_POINTERFOCUS_OUT_MS.
	 */
	PointerFocusable () : 
		PointerFocusable   (std::chrono::milliseconds(BWIDGETS_DEFAULT_POINTERFOCUS_IN_MS), 
					 std::chrono::milliseconds (BWIDGETS_DEFAULT_POINTERFOCUS_OUT_MS))
	{

	}

	/**
	 *  @brief  Constructs a PointerFocusable object.
	 *  @param focusInMs  Focus in time as std::chrono:ms.
	 *  @param focusOutMs  Focus out time as std::chrono:ms.
	 *
	 *  PointerFocusable objects may emit FocusEvents with the type POINTER_FOCUS_IN_EVENT
	 *  or POINTER_FOCUS_OUT_EVENT if the pointer rests over a widget.
	 */
	PointerFocusable (const std::chrono::milliseconds focusInMs, const std::chrono::milliseconds focusOutMs) :
		focusInMs_ (focusInMs), focusOutMs_ (focusOutMs) 
	{

	}

	/**
	 *  @brief  (Re-)defines the time to wait to emit a POINTER_FOCUS_IN_EVENT.
	 *  @param ms  Focus in time as std::chrono:ms.
	 */
	virtual void setFocusInMilliseconds (const std::chrono::milliseconds ms) 
	{
		focusInMs_ = ms;
	}

	/**
	 *  @brief  Gets the time to wait to emit a POINTER_FOCUS_IN_EVENT.
	 *  @return  Focus in time as std::chrono:ms.
	 */
	std::chrono::milliseconds getFocusInMilliseconds () const 
	{
		return focusInMs_;
	}

	/**
	 *  @brief  (Re-)defines the time to wait to emit a POINTER_FOCUS_OUT_EVENT.
	 *  @param ms  Focus out time as std::chrono:ms.
	 */
	virtual void setFocusOutMilliseconds (const std::chrono::milliseconds ms) 
	{
			focusOutMs_ = ms;
	}

	/**
	 *  @brief  Gets the time to wait to emit a POINTER_FOCUS_OUT_EVENT.
	 *  @return  Focus out time as std::chrono:ms.
	 */
	std::chrono::milliseconds getFocusOutMilliseconds () const 
	{
		return focusOutMs_;
	}

	/**
	 *  @brief  Informs if the pointer resting time is in the focus limits.
	 *  @param restMs  Pointer resting time as  std::chrono:ms.
	 */
	bool isFocusActive (const std::chrono::milliseconds restMs) const 
	{
		return ((restMs >= focusInMs_) && (restMs < focusOutMs_));
	}

    /**
     *  @brief  Switch widget focus support on/off.
     *  @param status  True if on, otherwise false.
     *
     *  Defines whether the widget may emit a FOCUS_XXX_EVENT if the pointer
	 *  rests over the widget for a given time. In this case, a PointerFocusEvent 
	 *  with the type POINTER_XXX_EVENT (with XXX is IN or OUT) will 
     *  be scheduled and send to the widget.
     */
    virtual void setFocusable (const bool status) {setSupport (status);}

    /**
     *  @brief  Information pointer button click support.
     *  @return  True if on, otherwise false.
     *
     *  If a widget is focusable, the main window event handler let the widget
     *  emit a PointerFocusEvent of the type POINER_XXX_EVENT (with XXX is IN or OUT) 
     *  if the pointer rests for a given time over the widget.
     */
    bool isFocusable () const {return getSupport();}

    /**
     *  @brief  Method called when focus in time is passed.
     *  @param event  Passed Event.
     *
     *  Overridable method called from the main window event scheduler when
     *  the time for focus in is passed. By default, it calls its static 
	 *  callback function.
     */
    virtual void onFocusIn (BEvents::Event* event)
    {
        callback (BEvents::Event::EventType::POINTER_FOCUS_IN_EVENT) (event);
    }

	/**
     *  @brief  Method called when focus out time is passed.
     *  @param event  Passed Event.
     *
     *  Overridable method called from the main window event scheduler when
     *  the time for focus out is passed. By default, it calls its static 
	 *  callback function.
     */
    virtual void onFocusOut (BEvents::Event* event)
    {
        callback (BEvents::Event::EventType::POINTER_FOCUS_OUT_EVENT) (event);
    }
};

}

#endif /*BWIDGETS_POINTERFOCUSABLE_HPP_*/
