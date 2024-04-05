
// Provide fake header guard for cpplint
#undef MYTP__TP_H_
#ifndef MYTP__TP_H_
#define MYTP__TP_H_

#undef TRACEPOINT_PROVIDER
#define TRACEPOINT_PROVIDER my_provider

#undef TRACEPOINT_INCLUDE
#define TRACEPOINT_INCLUDE "tp.h"

#if !defined(_MYTP__TP_H_) || defined(TRACEPOINT_HEADER_MULTI_READ)
#define _MYTP__TP_H_

#include <lttng/tracepoint.h>

#include <stdint.h>

TRACEPOINT_EVENT(
  TRACEPOINT_PROVIDER,
  my_tracepoint_does_not_work,
  TP_ARGS(
    const int64_t *, arr_arg,
    // Does not work
    const uint32_t, count_arg
    // Works
    // const uint64_t, count_arg
  ),
  TP_FIELDS(
    // Does not work
    ctf_sequence(int64_t, arr, arr_arg, uint32_t, count_arg)
    // Works
    // ctf_sequence(int64_t, arr, arr_arg, uint64_t, count_arg)
  )
)

#endif  // _MYTP__TP_H_

#include <lttng/tracepoint-event.h>

#endif  // MYTP__TP_H_
