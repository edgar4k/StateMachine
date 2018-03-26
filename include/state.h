/******************************************************************************
 * File: state.h
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
#ifndef STATE_H
#define STATE_H

#include <stdint.h>
#include <list.h>
#include "actionptr.h"
#include "stmevent.h"
#include "istatemachinenode.h"

class Transition;
class AbstractStateMachine;

/*!
 * \brief The State class
 */
class State : public IStateMachineNode
{
public:
    /*!
     * \brief State
     */
    State();
    /*!
     * \brief State
     * \param p
     */
    State(IStateMachineNode* p);
    virtual ~State() {}

    /*!
     * \brief enter
     * \param e
     */
    virtual void enter(StmEvent& e);

    /*!
     * \brief type
     * \return
     */
    virtual NodeType type() const { return NodeTypeState; }

    /*!
     * \brief setAction Sets the action member that is called whenever this state is entered
     * \param stm Address of the initialized statemachine
     * \param member - Address of the action member
     */
    template <class DerivedStm>
    void setAction(DerivedStm *stm, bool (DerivedStm::*action)(const StmEvent&)) { entryAction.setup(stm, action); }

    /*!
     * \brief setParent
     * \param p
     */
    void setParent(IStateMachineNode* p) { parent = p; }
    /*!
     * \brief getParent
     * \return
     */
    IStateMachineNode* getParent() const { return parent; }

    /*!
     * \brief getRoot
     * \return
     */
    IStateMachineNode* getRoot() const;

    /*!
     * \brief setId
     * \param id
     */
    void setId(uint32_t id) { stateId = id; }
    /*!
     * \brief getId
     * \return
     */
    uint32_t getId() const { return stateId; }

    /*!
     * \brief handleEvent
     * \param ev
     * \return
     */
    bool handleEvent(StmEvent& ev) const;

    /*!
     * \brief addTransition
     * \param tr
     */
    void addTransition(Transition* tr) { transitions.append(tr); }

    /*!
     * \brief operator ==
     * \param other
     * \return
     */
    bool operator == (const State& other) { return ( (other.stateId == stateId) && (other.parent == parent) ); }

protected:
    /*!
     * \brief action
     * \param e
     * \return
     */
    virtual bool action(const StmEvent& e) { return (hasAction()) ? entryAction(e) : false; }
    /*!
     * \brief hasAction
     * \return
     */
    virtual bool hasAction() const { return entryAction.valid(); }

private:
    State(const State&);
    State& operator = (const State&);

    uint32_t stateId;
    IStateMachineNode* parent;

    util::list<Transition*> transitions;

    ActionPtr entryAction;
};

#endif // STATE_H
