/*
 * Hsched_prv.h
 *
 *  Created on: Apr 2, 2022
 *      Author: Kishk
 */

#ifndef HSCHED_PRV_H_
#define HSCHED_PRV_H_

#define HSCHED_TRUE 			1
#define HSCHED_ZERO				0

#define HSCHED_MAXIMUM_TIMEMS	((u32) 0xFFFFFFFF)

static Sched_tstrRunnable * Tasks[HSCHED_MAXIMUM];
static void vidSched(void);
#endif /* HSCHED_PRV_H_ */
