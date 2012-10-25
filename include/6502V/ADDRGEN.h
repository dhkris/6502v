#ifndef ADDRGEN
#define ADDRGEN_LITTLEENDIAN(hi,lo) (((word)hi << 8) + (word)lo)
#define ADDRGEN_BIGENDIAN(hi,lo)(((word)hi >> 8) + (word)lo)

/* Default architecture assumes i386 */
#define ARCHSTR "unknown-arch (little endian)"
#define ADDRGEN ADDRGEN_LITTLEENDIAN

/* Architecture determination
      sets ARCHSTR and byte order */
#ifdef __i386__
   #undef ARCHSTR
   #undef ADDRGEN
   #define ADDRGEN ADDRGEN_LITTLEENDIAN
   #define ARCHSTR "x86-32 (little endian)"
#endif
#ifdef __x86_64__
   #undef ARCHSTR
   #undef ADDRGEN
   #define ADDRGEN ADDRGEN_LITTLEENDIAN
   #define ARCHSTR "x86-64 (little endian)"
#endif
#ifdef sparc64
   #undef ARCHSTR
   #undef ADDRGEN
   #define ADDRGEN ADDRGEN_BIGENDIAN
   #define ARCHSTR "sparc64 (big endian)"
#endif
#ifdef sparc
   #undef ARCHSTR
   #undef ADDRGEN
   #define ADDRGEN ADDRGEN_BIGENDIAN
   #define ARCHSTR "sparc32 (big endian)"   
#endif
#ifdef __sparc__
   #undef ARCHSTR
   #undef ADDRGEN
   #define ADDRGEN ADDRGEN_BIGENDIAN
   #define ARCHSTR "sparc32 (big endian)"   
#endif
#ifdef __sparc64__
   #undef ARCHSTR
   #undef ADDRGEN
   #define ADDRGEN ADDRGEN_BIGENDIAN
   #define ARCHSTR "sparc64 (big endian)"
#endif
#ifdef __ppc__
   #undef ARCHSTR
   #undef ADDRGEN
   #define ADDRGEN ADDRGEN_BIGENDIAN
   #define ARCHSTR "ppc32 (big endian)"   
#endif
#ifdef __ppc64__
   #undef ARCHSTR
   #undef ADDRGEN
   #define ADDRGEN ADDRGEN_BIGENDIAN
   #define ARCHSTR "ppc64 (big endian)"
#endif
#ifdef __arm__
   #undef ARCHSTR
   #undef ADDRGEN
   #define ADDRGEN ADDRGEN_BIGENDIAN   
   #define ARCHSTR "arm (big endian)"
#endif
#endif