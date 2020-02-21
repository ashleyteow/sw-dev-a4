#pragma once

#include "object.h"

//TODO_TREVOR Should the `Object`s be pointers or just normal?
class Array : public Object
{
public:
    Object **arr;
    int cap_;
    int len_;

    Array()
    {
        cap_ = 1;
        arr = new Object *[1]; 
        len_ = 0;
    }

    virtual ~Array() {
        delete this->arr;
    }

    /**
     * Allocates memory onto the Heap depending on the size of cap
     */
    void allocate_()
    {
        Object** temp_list = new Object* [cap_];
        for (int i = 0; i < this->len_; i++)
        {
            temp_list[i] = this->arr[i];
        }
        delete this->arr;
        this->arr = temp_list;
    }
    /**
         * Adds an item to the end of an array
         * @param item Object that will be added to an array
         */
    void push(Object *item)
    {
        this->insert(item, len_);
    }

    /**
         * Removes the last item of an array
         * @return the removed item
         */
    Object *pop()
    {
        return this->remove(this->len_ - 1);
    }

    /**
         * Gets the array's element at index
         * @param index The index at which the item will be retreived from
         * @return The object residing at the index
         */
    Object *get(size_t index)
    {
        return this->arr[index];
    }

    /**
         * Adds an item to the start of an array
         * @param item Object that will be added to an array
         */
    void addFront(Object *item)
    {
        this->insert(item, 0);
    }

    /**
         * Removes the first item of an array
         * @return The removed item
         */
    Object *removeFront()
    {
        return this->remove(0);
    }

    /**
         * Sets the array's element at index to the item
         * @param item The item to be inserted
         * @param index The index at which the item will be inserted
         * @return The object that was replaced
         */
    Object *set(Object *item, size_t index)
    {
        Object *ref = this->arr[index];
        this->arr[index] = item;
        return ref;
    }

    /**
         * Inserts the element at the given index
         * @param item The item to be inserted
         * @param index The index at which the item will be inserted
         * [1].insert(2, 0) -> [2, 1]
         */
    void insert(Object *item, size_t index)
    {
        assert(index <= this->len_);
        if (this->len_ + 1 > this->cap_)
        {
            this->cap_ *= 2;
            this->allocate_();
        }

        for (int j = this->len_; j > index; j--)
        {
            this->arr[j] = this->arr[j - 1];
        }
        this->arr[index] = item;
        this->len_++;
    }

    /**
         * Removes the element at the given index
         * @param index The index at which the item will be removed
         * @return The object that was removed
         */
    Object *remove(size_t index)
    {
        assert(this->length() > index);

        // Remove the item and shift all the strings over to the left
        Object* ret = this->arr[index];
        for (int j = index; j < this->len_ - 1; j++)
        {
            this->arr[j] = this->arr[j + 1];
        }

        // re-allocate if the size is less than the capacity
        if (this->length() < this->cap_ / 2)
        {
            this->cap_ /= 2;
            this->allocate_();
        }

        this->len_ --;
        return ret;
    }

    /**
         * Returns the length of the array
         * @return length of the array
         */
    size_t length()
    {
        return this->len_;
    }

    /**
         * Returns if the array contains the item
         * @return 1 if contains item, 0 otherwise
         */
    size_t contains(Object *item)
    {
        return this->indexOf(item) != -1;
    }

    /**
         * Returns the index of the item
         * @return index of the item. -1 if it does not contain the item
         */
    int indexOf(Object *item)
    {
        for (int i = 0; i < this->len_; i++)
        {
            if (this->arr[i]->equals(item))
            {
                return i;
            }
        }
        return -1;
    }
};