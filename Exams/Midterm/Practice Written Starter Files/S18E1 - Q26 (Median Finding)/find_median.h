/*
 * find_median.h
 * Univeristy of Michigan, Ann Arbor
 * EECS 281 S18E1 Q26.
 * DO NOT SUBMIT TO GRADESCOPE.
 * If submitted, this file will be ignored.
 */

#ifndef FIND_MEDIAN_H
#define FIND_MEDIAN_H

double find_median(double a[], int left, int right);


/*
 * Implemented by instructor code. Student does not need to implement these
 * functions.
 */
int partition(double a[], int left, int right);
double find_min(const double a[], int left, int right);

#endif
