/******************************************************************************
 * File: listelement.h
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
#ifndef LISTELEMENT_H
#define LISTELEMENT_H

namespace util
{

/*!
 * \brief The ListElement class
 */
template <typename E>
class ListElement
{
public:
    /*!
     * \brief ListElement
     */
    ListElement() : data(),next(nullptr) { }
    /*!
     * \brief ~ListElement
     */
    virtual ~ListElement() { if(next) { delete next; } }

    /*!
     * \brief data
     */
    E data;
    /*!
     * \brief next
     */
    ListElement* next;
private:
    ListElement(const ListElement&);
    ListElement& operator = (const ListElement&);
};

/*!
 * \brief The ListIterator class
 */
template <typename T>
class ListIterator
{
public:
    /*!
     * \brief ListIterator
     */
    ListIterator() : element(nullptr),invalidItem() {}
    /*!
     * \brief ListIterator
     * \param e
     */
    ListIterator(ListElement<T>* e) : element(e),invalidItem() {}
    /*!
     * \brief ListIterator
     * \param e
     * \param invalid
     */
    ListIterator(ListElement<T>* e, const T& invalid) : element(e),invalidItem(invalid) {}
    /*!
     * \brief ListIterator
     * \param other
     */
    ListIterator(const ListIterator& other) : element(other.element),invalidItem(other.invalidItem) {}
    virtual ~ListIterator() {}

    /*!
     * \brief operator =
     * \param other
     * \return
     */
    ListIterator& operator=(const ListIterator& other)
    {
        element = other.element;
        invalidItem = other.invalidItem;
        return *this;
    }

    /*!
     * \brief operator ++
     * \return
     */
    ListIterator& operator++()
    {
        if(nullptr != element)
        {
            element = element->next;
        }
        return *this;
    }

    /*!
     * \brief operator ++
     * \return
     */
    ListIterator operator++(int)
    {
        ListIterator tmp(*this);
        operator++();
        return tmp;
    }

    /*!
     * \brief operator ==
     * \param other
     * \return
     */
    bool operator==(const ListIterator& other)
    {
        return (other.element == element);
    }

    /*!
     * \brief operator !=
     * \param other
     * \return
     */
    bool operator!=(const ListIterator& other)
    {
        return (other.element != element);
    }

    /*!
     * \brief operator *
     * \return
     */
    T& operator*()
    {
        return (nullptr != element)?
                    element->data :
                    invalidItem;
    }

    /*!
     * \brief next
     * \return
     */
    ListIterator next()
    {
        return (nullptr != element)?
                    ListIterator(element->next) :
                    ListIterator();
    }

private:
    ListElement<T>* element;
    T invalidItem;
};

} // end namespace util

#endif // LISTELEMENT_H

