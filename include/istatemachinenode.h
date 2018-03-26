/******************************************************************************
 * File: istatemachinenode.h
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
#ifndef ISTATEMACHINENODE_H
#define ISTATEMACHINENODE_H

class StmEvent;

/*!
 * \brief The IStateMachineNode class
 */
class IStateMachineNode
{
public:
    /*!
     * \brief IStateMachineNode
     */
    IStateMachineNode() {}
    virtual ~IStateMachineNode() {}

    /*!
     * \brief The NodeType enum
     */
    enum NodeType
    {
        NodeTypeState,
        NodeTypeStateMachine,
        NodeTypeTransition,
        NodeTypeGuard
    };

    /*!
     * \brief type
     * \return
     */
    virtual NodeType type() const = 0;

protected:
    /*!
     * \brief action
     * \return
     */
    virtual bool action(const StmEvent&) = 0;
    /*!
     * \brief hasAction
     * \return
     */
    virtual bool hasAction() const = 0;

private:
    IStateMachineNode(const IStateMachineNode&);
    IStateMachineNode& operator = (const IStateMachineNode&);
};

#endif // ISTATEMACHINENODE_H
