/******************************************************************************
 * File: abstractstatemachine.h
 * Author: Edgar Hindemith
 * This file is part of the 'Simple Statemachine for Embedded Systems'
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
#ifndef ABSTRACTSTATEMACHINE_H
#define ABSTRACTSTATEMACHINE_H

#include "istatemachinenode.h"

class State;
class StmEvent;

/*!
 * \brief The AbstractStateMachine class
 */
class AbstractStateMachine : public IStateMachineNode
{
public:
    /*!
     * \brief AbstractStateMachine
     */
    AbstractStateMachine();

    /*!
     * \brief type
     * \return
     */
    virtual NodeType type() const { return NodeTypeStateMachine; }

    /*!
     * \brief setCurrentState
     * \param s
     */
    void setCurrentState(State* s) { currentState = s; }
    /*!
     * \brief getCurrentState
     * \return
     */
    State* getCurrentState() const { return currentState; }

    /*!
     * \brief startStateMachine
     */
    virtual void startStateMachine() = 0;
    /*!
     * \brief setUpStateMachine
     */
    virtual void setUpStateMachine() = 0;

    /*!
     * \brief handleEvent
     * \param ev
     * \return
     */
    bool handleEvent(StmEvent& ev) const;

protected:
    /*!
     * \brief action
     * \return
     */
    virtual bool action(const StmEvent&) { return false; }
    /*!
     * \brief hasAction
     * \return
     */
    virtual bool hasAction() const { return false; }

    /*!
     * \brief setInitialState
     * \param s
     */
    void setInitialState(State* s) { initialState = s; }
    /*!
     * \brief getInitialState
     * \return
     */
    State* getInitialState() { return initialState; }

private:
    AbstractStateMachine(const AbstractStateMachine&);
    AbstractStateMachine& operator =(const AbstractStateMachine&);

    State* currentState;
    State* initialState;
};

#endif // ABSTRACTSTATEMACHINE_H
