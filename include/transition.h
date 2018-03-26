/******************************************************************************
 * File: transition.h
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
#ifndef TRANSITION_H
#define TRANSITION_H

#include "actionptr.h"
#include "stmevent.h"
#include "istatemachinenode.h"

class AbstractStateMachine;

/*!
 * \brief The Transition class
 */
class Transition : public IStateMachineNode
{
public:
    /*!
     * \brief Transition
     */
    Transition();
    virtual ~Transition() {}

    /*!
     * \brief trigger
     * \param e
     */
    virtual void trigger(StmEvent& e);

    /*!
     * \brief type
     * \return
     */
    virtual NodeType type() const { return NodeTypeTransition; }

    /*!
     * \brief setAction Sets the action member that is called whenever this transition is triggered
     * \param stm Address of the initialized statemachine
     * \param member - Address of the action member
     */
    template <class DerivedStm>
    void setAction(DerivedStm *stm, bool (DerivedStm::*action)(const StmEvent&)) { trAction.setup(stm, action); }
    /*!
     * \brief setTarget
     * \param t
     */
    void setTarget(IStateMachineNode* t) { target = t; }
    /*!
     * \brief setEventType
     * \param type
     */
    void setEventType(int type) { eventType = type; }

    /*!
     * \brief operator ==
     * \param type
     * \return
     */
    bool operator == (const StmEvent::EventType type) const { return (type == eventType); }

protected:
    /*!
     * \brief action
     * \param e
     * \return
     */
    virtual bool action(const StmEvent& e) { return (hasAction()) ? trAction(e) : false; }
    /*!
     * \brief hasAction
     * \return
     */
    virtual bool hasAction() const { return trAction.valid(); }

private:
    Transition(const Transition&);
    Transition& operator = (const Transition&);

    IStateMachineNode* target;
    ActionPtr trAction;
    int eventType;
};

#endif // TRANSITION_H
