#include "trace.h"

static int trace_depth = 0;

uint8 TRACE_RUNTIME = 1;

int trace_depth_get() { return trace_depth; }

void __trace_ascend() { trace_depth++; }

void __trace_descend() { trace_depth--; }
