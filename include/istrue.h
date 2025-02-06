/*
 * istrue.h - Utility for determining if a value is true in C
 *
 * This header provides functions for determining if a given value is true.
 *
 * Author: Kevin Alavik <kevin@alavik.se>
 * License: Apache License 2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at:
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef _HUH_ISTRUE_H_
#define _HUH_ISTRUE_H_

#ifdef __cplusplus
extern "C"
{
#endif

    /**
     * istrue_scalar - Checks whether a scalar value is considered true.
     *
     * A scalar value is considered true if:
     * - It is non-zero for numeric types.
     *
     * @param value: A pointer to the scalar value to evaluate.
     * @return 1 if the scalar value is non-zero, otherwise 0.
     */
    int istrue_scalar(const void *value);

    /**
     * istrue_array - Checks whether all elements in an array are non-zero.
     *
     * An array is considered true if:
     * - All elements of the array are non-zero.
     *
     * @param value: A pointer to the array to evaluate.
     * @param size: The number of elements in the array.
     * @return 1 if all elements are non-zero, otherwise 0.
     */
    int istrue_array(const void *value, int size);

    /**
     * istrue - Checks whether a given value (scalar or array) is considered true.
     *
     * A value is considered true if:
     * - It is non-NULL.
     * - It is non-zero for scalar values.
     * - For arrays, every element is non-zero.
     *
     * @param value: A pointer to the value to evaluate.
     * @param size: The size of the value (used only for arrays).
     * @return 1 if the value is considered true, otherwise 0.
     */
    int istrue(const void *value, int size);

#ifdef ISTRUE_DEFINITION
    /**
     * Implementation of the istrue_scalar function.
     *
     * It checks if a scalar value is non-zero.
     *
     * @param value: The pointer to the scalar value to check.
     * @return 1 if the scalar value is non-zero, otherwise 0.
     */
    int istrue_scalar(const void *value)
    {
        if (value == NULL)
        {
            return 0;  // NULL pointer is considered false, not true
        }

        // For scalar values, check if it's non-zero
        return (*(const unsigned char *) value != 0);
    }

    /**
     * Implementation of the istrue_array function.
     *
     * It checks if all elements of an array are non-zero.
     *
     * @param value: The pointer to the array to check.
     * @param size: The number of elements in the array.
     * @return 1 If not all zero, otherwise 0.
     */
    int istrue_array(const void *value, int size)
    {
        if (value == NULL || size == 0)
        {
            return 0;  // NULL or empty array is considered false
        }

        const unsigned char *ptr   = (const unsigned char *) value;
        int                  zeros = 0;
        for (int i = 0; i < size; i++)
        {
            if (ptr[i] == 0)
                zeros++;
        }

        if (zeros != size)
            return 1;  // We got true
        else
            return 0;  // All elements are zero
    }

    /**
     * Implementation of the istrue function.
     *
     * It combines the scalar check and array check.
     *
     * @param value: The pointer to the value to check.
     * @param size: The size of the value (used only for arrays).
     * @return 1 if the value is considered true, otherwise 0.
     */
    int istrue(const void *value, int size)
    {
        if (value == NULL)
        {
            return 0;  // NULL pointer is considered false
        }

        // If size is zero, treat it as an empty buffer/array (false)
        if (size == 0)
        {
            return 0;  // Empty values are considered false
        }

        // If size is 1, treat it as a scalar value (non-array)
        if (size == sizeof(char))
        {
            return istrue_scalar(value);
        }

        // Otherwise, treat it as an array
        return istrue_array(value, size);
    }

#endif  // ISTRUE_DEFINITION

#ifdef __cplusplus
}
#endif

#endif  // _HUH_ISTRUE_H_
