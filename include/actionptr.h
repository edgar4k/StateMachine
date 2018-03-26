/******************************************************************************
 * File: actionptr.h
 * Author: Edgar Hindemith
 * This file is part of the 'Simple Statemachine for Embedded Systems'
 *
 * This file is based on the work in FP.h of Sam Grove
 * see http://mbed.org/users/sam_grove/code/FP/
 *
 * Copyright (C) 2016,2018 Edgar Hindemith
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *****************************************************************************/
#ifndef ACTIONPTR_H
#define ACTIONPTR_H

class StmEvent;
class AbstractStateMachine;

/*!
 * \brief The ActionPtr class
 * A class to add a statemachine member as a callback function to a state, choice or transition.
 */
class ActionPtr
{
public:
    /*!
     * \brief ActionPtr Ctor
     */
    ActionPtr() :
        stateMachine(nullptr),
        stmAction(nullptr)
    {}

    /*!
     * \brief setup Add a callback function
     * \param stm Address of the initialized statemachine
     * \param member - Address of the action member
     */
    template <class DerivedStm>
    void setup(DerivedStm *stm, bool (DerivedStm::*action)(const StmEvent&))
    {
        stateMachine = static_cast<AbstractStateMachine *>(stm);
        stmAction = (bool (AbstractStateMachine::*)(const StmEvent&))(action);
        return;
    }

    /*!
      * \brief operator () Invoke the attached function
      * \param ev The StmEvent argument that is passed into the action handler that is called
      * \return The return from the action hanlder called by this class
      */
     bool operator()(const StmEvent& ev) const
     {
         if( nullptr != stateMachine ) {
             return (stateMachine->*stmAction)(ev);
         }
         return false;
     }

    /*!
     * \brief valid Determine if an callback is currently hooked
     * \return 1 if a method is hooked, 0 otherwise
     */
    bool valid() const
    {
        return (static_cast<bool>(stateMachine) && static_cast<bool>(stmAction));
    }

    /*!
     * \brief remove Release a function from the callback hook
     */
    void remove()
    {
        stateMachine = nullptr;
        stmAction = nullptr;
    }

private:

    AbstractStateMachine *stateMachine;

    bool (AbstractStateMachine::*stmAction)(const StmEvent&);   /*!< Footprint for a member function */
};

#endif // ACTIONPTR_H
