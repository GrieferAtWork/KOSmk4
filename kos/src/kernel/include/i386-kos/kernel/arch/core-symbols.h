#include <hybrid/host.h>
#ifdef __x86_64__
#include "core-symbols64.h"
#else /* __x86_64__ */
#include "core-symbols32.h"
#endif /* !__x86_64__ */
