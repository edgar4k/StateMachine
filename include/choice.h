/******************************************************************************
 * File: choice.h
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
#ifndef CHOICE_H
#define CHOICE_H

#include "actionptr.h"
#include "istatemachinenode.h"

class StmEvent;
class Transition;
class AbstractStateMachine;

/*!
 * \brief The Choice class
 */
class Choice : public IStateMachineNode
{
public:
    /*!
     * \brief Choice
     */
    Choice();
    virtual ~Choice() {}

    /*!
     * \brief execute
     * \param e
     */
    virtual void execute(StmEvent& e);

    /*!
     * \brief type Gets the NodeType of this IStateMachineNode
     * \return IStateMachineNode
     */
    virtual NodeType type() const { return NodeTypeGuard; }

    /*!
     * \brief setCondition Sets an action returning bool to be the condition to decide for the first or second transition
     * \param stm Address of the initialized statemachine
     * \param member - Address of the action member
     */
    template <class DerivedStm>
    void setCondition(DerivedStm *stm, bool (DerivedStm::*action)(const StmEvent&)) { condition.setup(stm, action); }
    /*!
     * \brief setTransitions
     * \param t0
     * \param t1
     */
    void setTransitions(Transition* t0, Transition* t1) { target0 = t0; target1 = t1; }

protected:
    /*!
     * \brief action
     * \param e
     * \return
     */
    virtual bool action(const StmEvent& e) { return (hasAction()) ? condition(e) : false; }
    /*!
     * \brief hasAction
     * \return
     */
    virtual bool hasAction() const { return condition.valid(); }

private:
    Choice(const Choice&);
    Choice& operator = (const Choice&);

    Transition* target0;
    Transition* target1;
    ActionPtr condition;
};

#endif // CHOICE_H
