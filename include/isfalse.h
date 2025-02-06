/*
 * isfalse.h - Utility for determining if a value is false in C
 *
 * This header provides a functions for determining if a given value is false.
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

#ifndef _HUH_ISFALSE_H_
#define _HUH_ISFALSE_H_

#ifdef __cplusplus
extern "C"
{
#endif

    /**
     * isfalse_scalar - Checks whether a scalar value is considered false.
     *
     * A scalar value is considered false if:
     * - It is zero for numeric types.
     *
     * @param value: A pointer to the scalar value to evaluate.
     * @return 1 if the scalar value is zero, otherwise 0.
     */
    int isfalse_scalar(const void *value);

    /**
     * isfalse_array - Checks whether all elements in an array are zero.
     *
     * An array is considered false if:
     * - All elements of the array are zero.
     *
     * @param value: A pointer to the array to evaluate.
     * @param size: The number of elements in the array.
     * @return 1 if all elements are zero, otherwise 0.
     */
    int isfalse_array(const void *value, int size);

    /**
     * isfalse - Checks whether a given value (scalar or array) is considered false.
     *
     * A value is considered false if:
     * - It is NULL.
     * - It is zero for scalar values.
     * - For arrays, every element is zero.
     *
     * @param value: A pointer to the value to evaluate.
     * @param size: The size of the value (used only for arrays).
     * @return 1 if the value is considered false, otherwise 0.
     */
    int isfalse(const void *value, int size);

#ifdef ISFALSE_DEFINITION
    /**
     * Implementation of the isfalse_scalar function.
     *
     * It checks if a scalar value is zero.
     *
     * @param value: The pointer to the scalar value to check.
     * @return 1 if the scalar value is zero, otherwise 0.
     */
    int isfalse_scalar(const void *value)
    {
        if (value == NULL)
        {
            return 1;  // NULL pointer is considered false
        }

        // For scalar values, check if it's zero
        return (*(const unsigned char *) value == 0);
    }

    /**
     * Implementation of the isfalse_array function.
     *
     * It checks if all elements of an array are zero.
     *
     * @param value: The pointer to the array to check.
     * @param size: The number of elements in the array.
     * @return 1 if all elements are zero, otherwise 0.
     */
    int isfalse_array(const void *value, int size)
    {
        if (value == NULL || size == 0)
        {
            return 1;  // NULL or empty array is considered false
        }

        const unsigned char *ptr = (const unsigned char *) value;
        for (int i = 0; i < size; i++)
        {
            if (ptr[i] != 0)
            {
                return 0;  // Non-zero element found, not false
            }
        }

        return 1;  // All elements are zero
    }

    /**
     * Implementation of the isfalse function.
     *
     * It combines the scalar check and array check.
     *
     * @param value: The pointer to the value to check.
     * @param size: The size of the value (used only for arrays).
     * @return 1 if the value is considered false, otherwise 0.
     */
    int isfalse(const void *value, int size)
    {
        if (value == NULL)
        {
            return 1;  // NULL pointer is considered false
        }

        // If size is zero, treat it as an empty buffer/array (false)
        if (size == 0)
        {
            return 1;  // Empty values are considered false
        }

        // Check for scalar (non-array) value
        if (size == sizeof(char))
        {
            return isfalse_scalar(value);
        }

        // Check if it's an array of values
        return isfalse_array(value, size);
    }

#endif  // ISFALSE_DEFINITION

#ifdef __cplusplus
}
#endif

#endif  // _HUH_ISFALSE_H_
