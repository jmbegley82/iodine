/* Timing.h
 *
 */

#ifndef TIMING_H
#define TIMING_H

#ifdef __cplusplus
extern "C" {
#endif //__cplusplus

double GetTimeInMsec();
double GetTimeInUsec();
void SleepMsec(double ms);
void SleepUsec(int us);

#ifdef __cplusplus
}
#endif //__cplusplus

#endif //TIMING_H
