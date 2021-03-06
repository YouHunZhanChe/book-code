/*
    ReactOS
    Kernel Streaming API

    by Andrew Greenwood

    NOTES:
    This is a basic stubbing of the Kernel Streaming API header. It is
    very incomplete - a lot of the #defines are not set to any value at all.

    Some of the structs/funcs may be incorrectly grouped.

    GUIDs need to be defined properly.

    AVStream functionality (XP and above, DirectX 8.0 and above) will NOT
    implemented for a while.

    Some example code for interaction from usermode:
    DeviceIoControl(
        FilterHandle,
        IOCTL_KS_PROPERTY,
        &Property,
        sizeof(KSPROPERTY),
        &SeekingCapabilities,
        sizeof(KS_SEEKING_CAPABILITIES),
        &BytesReturned,
        &Overlapped);
*/

#ifndef _KS_
#define _KS_

#ifdef __cplusplus
extern "C" {
#endif

#ifdef BUILDING_KS
#define KSDDKAPI
#else
#define KSDDKAPI //DECLSPEC_IMPORT /* TODO */
#endif


#define KSFILTER_NODE   ((ULONG)-1)
#define KSALL_NODES     ((ULONG)-1)

#define KSSTRING_Filter L"{9B365890-165F-11D0-A195-0020AFD156E4}"
#define KSSTRING_Pin L"{146F1A80-4791-11D0-A5D6-28DB04C10000}"
#define KSSTRING_Clock L"{53172480-4791-11D0-A5D6-28DB04C10000}"
#define KSSTRING_Allocator L"{642F5D00-4791-11D0-A5D6-28DB04C10000}"
#define KSSTRING_AllocatorEx L"{091BB63B-603F-11D1-B067-00A0C9062802}"
#define KSSTRING_TopologyNode L"{0621061A-EE75-11D0-B915-00A0C9223196}"

#define KSDATAFORMAT_BIT_ATTRIBUTES                         1
#define KSDATAFORMAT_ATTRIBUTES                             (1 << KSDATAFORMAT_BIT_ATTRIBUTES)

#if defined(_NTDDK_)
typedef PVOID PKSWORKER;
#endif

#ifndef SIZEOF_ARRAY
#define SIZEOF_ARRAY(a)        (sizeof(a)/sizeof((a)[0]))
#endif

/* ===============================================================
    GUID definition helpers
*/

#ifndef _NTRTL_
#ifndef DEFINE_GUIDEX
#ifdef _MSC_VER
#define DEFINE_GUIDEX(name) EXTERN_C const CDECL GUID name
#else
#define DEFINE_GUIDEX(name) EXTERN_C const GUID name
#endif
#endif

#ifndef STATICGUIDOF
#define STATICGUIDOF(guid) STATIC_##guid
#endif
#endif

#if defined(__cplusplus) && _MSC_VER >= 1100
#define DEFINE_GUIDSTRUCT(guid, name) struct __declspec(uuid(guid)) name
#define DEFINE_GUIDNAMED(name) __uuidof(struct name)
#else
#define DEFINE_GUIDSTRUCT(guid, name) DEFINE_GUIDEX(name)
#define DEFINE_GUIDNAMED(name) name
#endif


#define STATIC_GUID_NULL \
    0x00000000L, 0x0000, 0x0000, {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}
DEFINE_GUIDSTRUCT("00000000-0000-0000-0000-000000000000", GUID_NULL);
#define GUID_NULL DEFINE_GUIDNAMED(GUID_NULL)


#define STATIC_KSNAME_Filter\
    0x9b365890L, 0x165f, 0x11d0, {0xa1, 0x95, 0x00, 0x20, 0xaf, 0xd1, 0x56, 0xe4}
DEFINE_GUIDSTRUCT("9b365890-165f-11d0-a195-0020afd156e4", KSNAME_Filter);
#define KSNAME_Filter DEFINE_GUIDNAMED(KSNAME_Filter)

#define STATIC_KSMEMORY_TYPE_KERNEL_PAGED \
    0xd833f8f8L, 0x7894, 0x11d1, {0xb0, 0x69, 0x00, 0xa0, 0xc9, 0x06, 0x28, 0x02}
DEFINE_GUIDSTRUCT("d833f8f8-7894-11d1-b069-00a0c9062802", KSMEMORY_TYPE_KERNEL_PAGED);
#define KSMEMORY_TYPE_KERNEL_PAGED  DEFINE_GUIDNAMED(KSMEMORY_TYPE_KERNEL_PAGED)

/* ===============================================================
    I/O Control Codes
*/

#define IOCTL_KS_DISABLE_EVENT \
    CTL_CODE( \
              FILE_DEVICE_KS, \
              0x000, \
              METHOD_NEITHER, \
              FILE_ANY_ACCESS)

#define IOCTL_KS_ENABLE_EVENT \
    CTL_CODE( \
              FILE_DEVICE_KS, \
              0x001, \
              METHOD_NEITHER, \
              FILE_ANY_ACCESS)

// WAS 2
#define IOCTL_KS_METHOD \
    CTL_CODE( \
              FILE_DEVICE_KS, \
              0x003, \
              METHOD_NEITHER, \
              FILE_ANY_ACCESS)

// WAS 3
#define IOCTL_KS_PROPERTY \
    CTL_CODE( \
              FILE_DEVICE_KS, \
              0x000, \
              METHOD_NEITHER, \
              FILE_ANY_ACCESS)

#define IOCTL_KS_WRITE_STREAM \
    CTL_CODE( \
              FILE_DEVICE_KS, \
              0x004, \
              METHOD_NEITHER, \
              FILE_WRITE_ACCESS)

#define IOCTL_KS_READ_STREAM \
    CTL_CODE( \
              FILE_DEVICE_KS, \
              0x005, \
              METHOD_NEITHER, \
              FILE_READ_ACCESS)

#define IOCTL_KS_RESET_STATE \
    CTL_CODE( \
              FILE_DEVICE_KS, \
              0x006, \
              METHOD_NEITHER, \
              FILE_ANY_ACCESS)


/* ===============================================================
    Categories
*/

#define STATIC_KSCATEGORY_BRIDGE \
    0x085AFF00L, 0x62CE, 0x11CF, {0xA5, 0xD6, 0x28, 0xDB, 0x04, 0xC1, 0x00, 0x00}
DEFINE_GUIDSTRUCT("085AFF00-62CE-11CF-A5D6-28DB04C10000", KSCATEGORY_BRIDGE);
#define KSCATEGORY_BRIDGE DEFINE_GUIDNAMED(KSCATEGORY_BRIDGE)

#define STATIC_KSCATEGORY_CAPTURE \
    0x65E8773DL, 0x8F56, 0x11D0, {0xA3, 0xB9, 0x00, 0xA0, 0xC9, 0x22, 0x31, 0x96}
DEFINE_GUIDSTRUCT("65E8773D-8F56-11D0-A3B9-00A0C9223196", KSCATEGORY_CAPTURE);
#define KSCATEGORY_CAPTURE DEFINE_GUIDNAMED(KSCATEGORY_CAPTURE)

#define STATIC_KSCATEGORY_RENDER \
    0x65E8773EL, 0x8F56, 0x11D0, {0xA3, 0xB9, 0x00, 0xA0, 0xC9, 0x22, 0x31, 0x96}
DEFINE_GUIDSTRUCT("65E8773E-8F56-11D0-A3B9-00A0C9223196", KSCATEGORY_RENDER);
#define KSCATEGORY_RENDER DEFINE_GUIDNAMED(KSCATEGORY_RENDER)

#define STATIC_KSCATEGORY_MIXER \
    0xAD809C00L, 0x7B88, 0x11D0, {0xA5, 0xD6, 0x28, 0xDB, 0x04, 0xC1, 0x00, 0x00}
DEFINE_GUIDSTRUCT("AD809C00-7B88-11D0-A5D6-28DB04C10000", KSCATEGORY_MIXER);
#define KSCATEGORY_MIXER DEFINE_GUIDNAMED(KSCATEGORY_MIXER)

#define STATIC_KSCATEGORY_SPLITTER \
    0x0A4252A0L, 0x7E70, 0x11D0, {0xA5, 0xD6, 0x28, 0xDB, 0x04, 0xC1, 0x00, 0x00}
DEFINE_GUIDSTRUCT("0A4252A0-7E70-11D0-A5D6-28DB04C10000", KSCATEGORY_SPLITTER);
#define KSCATEGORY_SPLITTER DEFINE_GUIDNAMED(KSCATEGORY_SPLITTER)

#define STATIC_KSCATEGORY_DATACOMPRESSOR \
    0x1E84C900L, 0x7E70, 0x11D0, {0xA5, 0xD6, 0x28, 0xDB, 0x04, 0xC1, 0x00, 0x00}
DEFINE_GUIDSTRUCT("1E84C900-7E70-11D0-A5D6-28DB04C10000", KSCATEGORY_DATACOMPRESSOR);
#define KSCATEGORY_DATACOMPRESSOR DEFINE_GUIDNAMED(KSCATEGORY_DATACOMPRESSOR)

#define STATIC_KSCATEGORY_DATADECOMPRESSOR \
    0x2721AE20L, 0x7E70, 0x11D0, {0xA5, 0xD6, 0x28, 0xDB, 0x04, 0xC1, 0x00, 0x00}
DEFINE_GUIDSTRUCT("2721AE20-7E70-11D0-A5D6-28DB04C10000", KSCATEGORY_DATADECOMPRESSOR);
#define KSCATEGORY_DATADECOMPRESSOR DEFINE_GUIDNAMED(KSCATEGORY_DATADECOMPRESSOR)

#define STATIC_KSCATEGORY_DATATRANSFORM \
    0x2EB07EA0L, 0x7E70, 0x11D0, {0xA5, 0xD6, 0x28, 0xDB, 0x04, 0xC1, 0x00, 0x00}
DEFINE_GUIDSTRUCT("2EB07EA0-7E70-11D0-A5D6-28DB04C10000", KSCATEGORY_DATATRANSFORM);
#define KSCATEGORY_DATATRANSFORM DEFINE_GUIDNAMED(KSCATEGORY_DATATRANSFORM)

#define STATIC_KSCATEGORY_COMMUNICATIONSTRANSFORM \
    0xCF1DDA2CL, 0x9743, 0x11D0, {0xA3, 0xEE, 0x00, 0xA0, 0xC9, 0x22, 0x31, 0x96}
DEFINE_GUIDSTRUCT("CF1DDA2C-9743-11D0-A3EE-00A0C9223196", KSCATEGORY_COMMUNICATIONSTRANSFORM);
#define KSCATEGORY_COMMUNICATIONSTRANSFORM DEFINE_GUIDNAMED(KSCATEGORY_COMMUNICATIONSTRANSFORM)

#define STATIC_KSCATEGORY_INTERFACETRANSFORM \
    0xCF1DDA2DL, 0x9743, 0x11D0, {0xA3, 0xEE, 0x00, 0xA0, 0xC9, 0x22, 0x31, 0x96}
DEFINE_GUIDSTRUCT("CF1DDA2D-9743-11D0-A3EE-00A0C9223196", KSCATEGORY_INTERFACETRANSFORM);
#define KSCATEGORY_INTERFACETRANSFORM DEFINE_GUIDNAMED(KSCATEGORY_INTERFACETRANSFORM)

#define STATIC_KSCATEGORY_MEDIUMTRANSFORM \
    0xCF1DDA2EL, 0x9743, 0x11D0, {0xA3, 0xEE, 0x00, 0xA0, 0xC9, 0x22, 0x31, 0x96}
DEFINE_GUIDSTRUCT("CF1DDA2E-9743-11D0-A3EE-00A0C9223196", KSCATEGORY_MEDIUMTRANSFORM);
#define KSCATEGORY_MEDIUMTRANSFORM DEFINE_GUIDNAMED(KSCATEGORY_MEDIUMTRANSFORM)

#define STATIC_KSCATEGORY_FILESYSTEM \
    0x760FED5EL, 0x9357, 0x11D0, {0xA3, 0xCC, 0x00, 0xA0, 0xC9, 0x22, 0x31, 0x96}
DEFINE_GUIDSTRUCT("760FED5E-9357-11D0-A3CC-00A0C9223196", KSCATEGORY_FILESYSTEM);
#define KSCATEGORY_FILESYSTEM DEFINE_GUIDNAMED(KSCATEGORY_FILESYSTEM)

#define STATIC_KSCATEGORY_CLOCK \
    0x53172480L, 0x4791, 0x11D0, {0xA5, 0xD6, 0x28, 0xDB, 0x04, 0xC1, 0x00, 0x00}
DEFINE_GUIDSTRUCT("53172480-4791-11D0-A5D6-28DB04C10000", KSCATEGORY_CLOCK);
#define KSCATEGORY_CLOCK DEFINE_GUIDNAMED(KSCATEGORY_CLOCK)

#define STATIC_KSCATEGORY_PROXY \
    0x97EBAACAL, 0x95BD, 0x11D0, {0xA3, 0xEA, 0x00, 0xA0, 0xC9, 0x22, 0x31, 0x96}
DEFINE_GUIDSTRUCT("97EBAACA-95BD-11D0-A3EA-00A0C9223196", KSCATEGORY_PROXY);
#define KSCATEGORY_PROXY DEFINE_GUIDNAMED(KSCATEGORY_PROXY)

#define STATIC_KSCATEGORY_QUALITY \
    0x97EBAACBL, 0x95BD, 0x11D0, {0xA3, 0xEA, 0x00, 0xA0, 0xC9, 0x22, 0x31, 0x96}
DEFINE_GUIDSTRUCT("97EBAACB-95BD-11D0-A3EA-00A0C9223196", KSCATEGORY_QUALITY);
#define KSCATEGORY_QUALITY DEFINE_GUIDNAMED(KSCATEGORY_QUALITY)

/* ===============================================================
    Common
*/

typedef struct {
    GUID Set;
    ULONG Id;
    ULONG Flags;
} KSIDENTIFIER, *PKSIDENTIFIER;

typedef KSIDENTIFIER KSPROPERTY, *PKSPROPERTY;
typedef KSIDENTIFIER KSMETHOD, *PKSMETHOD;
typedef KSIDENTIFIER KSEVENT, *PKSEVENT;

typedef KSIDENTIFIER KSDEGRADE, *PKSDEGRADE;

typedef KSIDENTIFIER KSPIN_INTERFACE, *PKSPIN_INTERFACE;
typedef KSIDENTIFIER KSPIN_MEDIUM, *PKSPIN_MEDIUM;

typedef union {
    struct {
        ULONG   FormatSize;
        ULONG   Flags;
        ULONG   SampleSize;
        ULONG   Reserved;
        GUID    MajorFormat;
        GUID    SubFormat;
        GUID    Specifier;
    };
    LONGLONG    Alignment;
} KSDATAFORMAT, *PKSDATAFORMAT, KSDATARANGE, *PKSDATARANGE;


typedef struct {
    ULONG Size;
    ULONG Flags;
    GUID Attribute;
} KSATTRIBUTE, *PKSATTRIBUTE;



/* ===============================================================
    Interface Sets - TODO
*/

#if 0
#define KSINTERFACESETID_Media

#define KSINTERFACE_STANDARD_STREAMING
#define KSINTERFACE_STANDARD_LOOPED_STREAMING
#define KSINTERFACE_STANDARD_CONTROL
#endif

#define STATIC_KSINTERFACESETID_Standard \
    0x1A8766A0L, 0x62CE, 0x11CF, {0xA5, 0xD6, 0x28, 0xDB, 0x04, 0xC1, 0x00, 0x00}
DEFINE_GUIDSTRUCT("1A8766A0-62CE-11CF-A5D6-28DB04C10000", KSINTERFACESETID_Standard);
#define KSINTERFACESETID_Standard DEFINE_GUIDNAMED(KSINTERFACESETID_Standard)

typedef enum {
    KSINTERFACE_STANDARD_STREAMING,
    KSINTERFACE_STANDARD_LOOPED_STREAMING,
    KSINTERFACE_STANDARD_CONTROL
} KSINTERFACE_STANDARD;

#define STATIC_KSINTERFACESETID_FileIo \
    0x8C6F932CL, 0xE771, 0x11D0, {0xB8, 0xFF, 0x00, 0xA0, 0xC9, 0x22, 0x31, 0x96}
DEFINE_GUIDSTRUCT("8C6F932C-E771-11D0-B8FF-00A0C9223196", KSINTERFACESETID_FileIo);
#define KSINTERFACESETID_FileIo DEFINE_GUIDNAMED(KSINTERFACESETID_FileIo)




/* ===============================================================
    Mediums
*/

typedef enum {
    KSINTERFACE_FILEIO_STREAMING
} KSINTERFACE_FILEIO;

#define KSMEDIUM_TYPE_ANYINSTANCE       0

#define STATIC_KSMEDIUMSETID_Standard \
    0x4747B320L, 0x62CE, 0x11CF, {0xA5, 0xD6, 0x28, 0xDB, 0x04, 0xC1, 0x00, 0x00}
DEFINE_GUIDSTRUCT("4747B320-62CE-11CF-A5D6-28DB04C10000", KSMEDIUMSETID_Standard);
#define KSMEDIUMSETID_Standard DEFINE_GUIDNAMED(KSMEDIUMSETID_Standard)


/* ===============================================================
    Clock Properties/Methods/Events
*/

#define STATIC_KSPROPSETID_Clock \
    0xDF12A4C0L, 0xAC17, 0x11CF, {0xA5, 0xD6, 0x28, 0xDB, 0x04, 0xC1, 0x00, 0x00}
DEFINE_GUIDSTRUCT("DF12A4C0-AC17-11CF-A5D6-28DB04C10000", KSPROPSETID_Clock);
#define KSPROPSETID_Clock DEFINE_GUIDNAMED(KSPROPSETID_Clock)

typedef enum {
    KSPROPERTY_CLOCK_TIME,
    KSPROPERTY_CLOCK_PHYSICALTIME,
    KSPROPERTY_CLOCK_CORRELATEDTIME,
    KSPROPERTY_CLOCK_CORRELATEDPHYSICALTIME,
    KSPROPERTY_CLOCK_RESOLUTION,
    KSPROPERTY_CLOCK_STATE,
#if defined(_NTDDK_)
    KSPROPERTY_CLOCK_FUNCTIONTABLE
#endif // defined(_NTDDK_)
} KSPROPERTY_CLOCK;

#define STATIC_KSEVENTSETID_Clock \
    0x364D8E20L, 0x62C7, 0x11CF, {0xA5, 0xD6, 0x28, 0xDB, 0x04, 0xC1, 0x00, 0x00}
DEFINE_GUIDSTRUCT("364D8E20-62C7-11CF-A5D6-28DB04C10000", KSEVENTSETID_Clock);
#define KSEVENTSETID_Clock DEFINE_GUIDNAMED(KSEVENTSETID_Clock)

typedef enum {
    KSEVENT_CLOCK_INTERVAL_MARK,
    KSEVENT_CLOCK_POSITION_MARK
} KSEVENT_CLOCK_POSITION;


/* ===============================================================
    Connection Properties/Methods/Events
*/

#define STATIC_KSPROPSETID_Connection \
    0x1D58C920L, 0xAC9B, 0x11CF, {0xA5, 0xD6, 0x28, 0xDB, 0x04, 0xC1, 0x00, 0x00}
DEFINE_GUIDSTRUCT("1D58C920-AC9B-11CF-A5D6-28DB04C10000", KSPROPSETID_Connection);
#define KSPROPSETID_Connection DEFINE_GUIDNAMED(KSPROPSETID_Connection)


typedef enum {
    KSPROPERTY_CONNECTION_STATE,
    KSPROPERTY_CONNECTION_PRIORITY,
    KSPROPERTY_CONNECTION_DATAFORMAT,
    KSPROPERTY_CONNECTION_ALLOCATORFRAMING,
    KSPROPERTY_CONNECTION_PROPOSEDATAFORMAT,
    KSPROPERTY_CONNECTION_ACQUIREORDERING,
    KSPROPERTY_CONNECTION_ALLOCATORFRAMING_EX,
    KSPROPERTY_CONNECTION_STARTAT
} KSPROPERTY_CONNECTION;

#define DEFINE_KSPROPERTY_ITEM_CONNECTION_STATE(GetHandler, SetHandler)\
    DEFINE_KSPROPERTY_ITEM(\
                           KSPROPERTY_CONNECTION_STATE,\
                           (GetHandler),\
                           sizeof(KSPROPERTY),\
                           sizeof(KSSTATE),\
                           (SetHandler),\
                           NULL, 0, NULL, NULL, 0)

#define DEFINE_KSPROPERTY_ITEM_CONNECTION_PRIORITY(GetHandler, SetHandler)\
    DEFINE_KSPROPERTY_ITEM(\
                           KSPROPERTY_CONNECTION_PRIORITY,\
                           (GetHandler),\
                           sizeof(KSPROPERTY),\
                           sizeof(KSPRIORITY),\
                           (SetHandler),\
                           NULL, 0, NULL, NULL, 0)

#define DEFINE_KSPROPERTY_ITEM_CONNECTION_DATAFORMAT(GetHandler, SetHandler)\
    DEFINE_KSPROPERTY_ITEM(\
                           KSPROPERTY_CONNECTION_DATAFORMAT,\
                           (GetHandler),\
                           sizeof(KSPROPERTY),\
                           0,\
                           (SetHandler),\
                           NULL, 0, NULL, NULL, 0)

#define DEFINE_KSPROPERTY_ITEM_CONNECTION_ALLOCATORFRAMING(Handler)\
    DEFINE_KSPROPERTY_ITEM(\
                           KSPROPERTY_CONNECTION_ALLOCATORFRAMING,\
                           (Handler),\
                           sizeof(KSPROPERTY),\
                           sizeof(KSALLOCATOR_FRAMING),\
                           NULL, NULL, 0, NULL, NULL, 0)

#define DEFINE_KSPROPERTY_ITEM_CONNECTION_ALLOCATORFRAMING_EX(Handler)\
    DEFINE_KSPROPERTY_ITEM(\
                           KSPROPERTY_CONNECTION_ALLOCATORFRAMING_EX,\
                           (Handler),\
                           sizeof(KSPROPERTY),\
                           0,\
                           NULL, NULL, 0, NULL, NULL, 0)

#define DEFINE_KSPROPERTY_ITEM_CONNECTION_PROPOSEDATAFORMAT(Handler)\
    DEFINE_KSPROPERTY_ITEM(\
                           KSPROPERTY_CONNECTION_PROPOSEDATAFORMAT,\
                           NULL,\
                           sizeof(KSPROPERTY),\
                           sizeof(KSDATAFORMAT),\
                           (Handler),\
                           NULL, 0, NULL, NULL, 0)

#define DEFINE_KSPROPERTY_ITEM_CONNECTION_ACQUIREORDERING(Handler)\
    DEFINE_KSPROPERTY_ITEM(\
                           KSPROPERTY_CONNECTION_ACQUIREORDERING,\
                           (Handler),\
                           sizeof(KSPROPERTY),\
                           sizeof(int),\
                           NULL, NULL, 0, NULL, NULL, 0)

#define DEFINE_KSPROPERTY_ITEM_CONNECTION_STARTAT(Handler)\
    DEFINE_KSPROPERTY_ITEM(\
                           KSPROPERTY_CONNECTION_STARTAT,\
                           NULL,\
                           sizeof(KSPROPERTY),\
                           sizeof(KSRELATIVEEVENT),\
                           (Handler),\
                           NULL, 0, NULL, NULL, 0)


typedef enum {
    KSEVENT_CONNECTION_POSITIONUPDATE,
    KSEVENT_CONNECTION_DATADISCONTINUITY,
    KSEVENT_CONNECTION_TIMEDISCONTINUITY,
    KSEVENT_CONNECTION_PRIORITY,
    KSEVENT_CONNECTION_ENDOFSTREAM
} KSEVENT_CONNECTION;


/* ===============================================================
    General
    Properties/Methods/Events
*/

#define STATIC_KSPROPSETID_General\
    0x1464EDA5L, 0x6A8F, 0x11D1, {0x9A, 0xA7, 0x00, 0xA0, 0xC9, 0x22, 0x31, 0x96}
DEFINE_GUIDSTRUCT("1464EDA5-6A8F-11D1-9AA7-00A0C9223196", KSPROPSETID_General);
#define KSPROPSETID_General DEFINE_GUIDNAMED(KSPROPSETID_General)


typedef enum {
    KSPROPERTY_GENERAL_COMPONENTID
} KSPROPERTY_GENERAL;


/* ===============================================================
    Graph Manager
    Properties/Methods/Events
*/

#define KSPROPSETID_GM \
    0xAF627536L, 0xE719, 0x11D2, {0x8A, 0x1D, 0x00, 0x60, 0x97, 0xD2, 0xDF, 0x5D}

typedef enum {
    KSPROPERTY_GM_GRAPHMANAGER,
    KSPROPERTY_GM_TIMESTAMP_CLOCK,
    KSPROPERTY_GM_RATEMATCH,
    KSPROPERTY_GM_RENDERCLOCK
} KSPROPERTY_GM;


/* ===============================================================
    Media Seeking
    Properties/Methods/Events
*/

#define STATIC_KSPROPSETID_MediaSeeking\
    0xEE904F0CL, 0xD09B, 0x11D0, {0xAB, 0xE9, 0x00, 0xA0, 0xC9, 0x22, 0x31, 0x96}
DEFINE_GUIDSTRUCT("EE904F0C-D09B-11D0-ABE9-00A0C9223196", KSPROPSETID_MediaSeeking);
#define KSPROPSETID_MediaSeeking DEFINE_GUIDNAMED(KSPROPSETID_MediaSeeking)

typedef enum {
    KSPROPERTY_MEDIASEEKING_CAPABILITIES,
    KSPROPERTY_MEDIASEEKING_FORMATS,
    KSPROPERTY_MEDIASEEKING_TIMEFORMAT,
    KSPROPERTY_MEDIASEEKING_POSITION,
    KSPROPERTY_MEDIASEEKING_STOPPOSITION,
    KSPROPERTY_MEDIASEEKING_POSITIONS,
    KSPROPERTY_MEDIASEEKING_DURATION,
    KSPROPERTY_MEDIASEEKING_AVAILABLE,
    KSPROPERTY_MEDIASEEKING_PREROLL,
    KSPROPERTY_MEDIASEEKING_CONVERTTIMEFORMAT
} KSPROPERTY_MEDIASEEKING;

typedef enum {
    KS_SEEKING_NoPositioning,
    KS_SEEKING_AbsolutePositioning,
    KS_SEEKING_RelativePositioning,
    KS_SEEKING_IncrementalPositioning,
    KS_SEEKING_PositioningBitsMask = 0x3,
    KS_SEEKING_SeekToKeyFrame,
    KS_SEEKING_ReturnTime = 0x8
} KS_SEEKING_FLAGS;

typedef enum {
    KS_SEEKING_CanSeekAbsolute = 0x1,
    KS_SEEKING_CanSeekForwards = 0x2,
    KS_SEEKING_CanSeekBackwards = 0x4,
    KS_SEEKING_CanGetCurrentPos = 0x8,
    KS_SEEKING_CanGetStopPos = 0x10,
    KS_SEEKING_CanGetDuration = 0x20,
    KS_SEEKING_CanPlayBackwards = 0x40
} KS_SEEKING_CAPABILITIES;

typedef struct {
    LONGLONG            Current;
    LONGLONG            Stop;
    KS_SEEKING_FLAGS    CurrentFlags;
    KS_SEEKING_FLAGS    StopFlags;
} KSPROPERTY_POSITIONS, *PKSPROPERTY_POSITIONS;

typedef struct {
    LONGLONG    Earliest;
    LONGLONG    Latest;
} KSPROPERTY_MEDIAAVAILABLE, *PKSPROPERTY_MEDIAAVAILABLE;

typedef struct {
    KSPROPERTY  Property;
    GUID        SourceFormat;
    GUID        TargetFormat;
    LONGLONG    Time;
} KSP_TIMEFORMAT, *PKSP_TIMEFORMAT;

#define DEFINE_KSPROPERTY_ITEM_MEDIASEEKING_CAPABILITIES(Handler)\
    DEFINE_KSPROPERTY_ITEM(\
                           KSPROPERTY_MEDIASEEKING_CAPABILITIES,\
                           (Handler),\
                           sizeof(KSPROPERTY),\
                           sizeof(KS_SEEKING_CAPABILITIES),\
                           NULL, NULL, 0, NULL, NULL, 0)

#define DEFINE_KSPROPERTY_ITEM_MEDIASEEKING_FORMATS(Handler)\
    DEFINE_KSPROPERTY_ITEM(\
                           KSPROPERTY_MEDIASEEKING_FORMATS,\
                           (Handler),\
                           sizeof(KSPROPERTY),\
                           0,\
                           NULL, NULL, 0, NULL, NULL, 0)

#define DEFINE_KSPROPERTY_ITEM_MEDIASEEKING_TIMEFORMAT(GetHandler, SetHandler)\
    DEFINE_KSPROPERTY_ITEM(\
                           KSPROPERTY_MEDIASEEKING_TIMEFORMAT,\
                           (GetHandler),\
                           sizeof(KSPROPERTY),\
                           sizeof(GUID),\
                           (SetHandler),\
                           NULL, 0, NULL, NULL, 0)

#define DEFINE_KSPROPERTY_ITEM_MEDIASEEKING_POSITION(Handler)\
    DEFINE_KSPROPERTY_ITEM(\
                           KSPROPERTY_MEDIASEEKING_POSITION,\
                           (Handler),\
                           sizeof(KSPROPERTY),\
                           sizeof(LONGLONG),\
                           NULL, NULL, 0, NULL, NULL, 0)

#define DEFINE_KSPROPERTY_ITEM_MEDIASEEKING_STOPPOSITION(Handler)\
    DEFINE_KSPROPERTY_ITEM(\
                           KSPROPERTY_MEDIASEEKING_STOPPOSITION,\
                           (Handler),\
                           sizeof(KSPROPERTY),\
                           sizeof(LONGLONG),\
                           NULL, NULL, 0, NULL, NULL, 0)

#define DEFINE_KSPROPERTY_ITEM_MEDIASEEKING_POSITIONS(Handler)\
    DEFINE_KSPROPERTY_ITEM(\
                           KSPROPERTY_MEDIASEEKING_POSITIONS,\
                           NULL,\
                           sizeof(KSPROPERTY),\
                           sizeof(KSPROPERTY_POSITIONS),\
                           (Handler),\
                           NULL, 0, NULL, NULL, 0)

#define DEFINE_KSPROPERTY_ITEM_MEDIASEEKING_DURATION(Handler)\
    DEFINE_KSPROPERTY_ITEM(\
                           KSPROPERTY_MEDIASEEKING_DURATION,\
                           (Handler),\
                           sizeof(KSPROPERTY),\
                           sizeof(LONGLONG),\
                           NULL, NULL, 0, NULL, NULL, 0)

#define DEFINE_KSPROPERTY_ITEM_MEDIASEEKING_AVAILABLE(Handler)\
    DEFINE_KSPROPERTY_ITEM(\
                           KSPROPERTY_MEDIASEEKING_AVAILABLE,\
                           (Handler),\
                           sizeof(KSPROPERTY),\
                           sizeof(KSPROPERTY_MEDIAAVAILABLE),\
                           NULL, NULL, 0, NULL, NULL, 0)

#define DEFINE_KSPROPERTY_ITEM_MEDIASEEKING_PREROLL(Handler)\
    DEFINE_KSPROPERTY_ITEM(\
                           KSPROPERTY_MEDIASEEKING_PREROLL,\
                           (Handler),\
                           sizeof(KSPROPERTY),\
                           sizeof(LONGLONG),\
                           NULL, NULL, 0, NULL, NULL, 0)

#define DEFINE_KSPROPERTY_ITEM_MEDIASEEKING_CONVERTTIMEFORMAT(Handler)\
    DEFINE_KSPROPERTY_ITEM(\
                           KSPROPERTY_MEDIASEEKING_CONVERTTIMEFORMAT,\
                           (Handler),\
                           sizeof(KSP_TIMEFORMAT),\
                           sizeof(LONGLONG),\
                           NULL, NULL, 0, NULL, NULL, 0)

/* ===============================================================
    Pin
    Properties/Methods/Events
*/

#define STATIC_KSPROPSETID_Pin\
    0x8C134960L, 0x51AD, 0x11CF, {0x87, 0x8A, 0x94, 0xF8, 0x01, 0xC1, 0x00, 0x00}
DEFINE_GUIDSTRUCT("8C134960-51AD-11CF-878A-94F801C10000", KSPROPSETID_Pin);
#define KSPROPSETID_Pin DEFINE_GUIDNAMED(KSPROPSETID_Pin)

#define STATIC_KSNAME_Pin\
    0x146F1A80L, 0x4791, 0x11D0, {0xA5, 0xD6, 0x28, 0xDB, 0x04, 0xC1, 0x00, 0x00}
DEFINE_GUIDSTRUCT("146F1A80-4791-11D0-A5D6-28DB04C10000", KSNAME_Pin);
#define KSNAME_Pin DEFINE_GUIDNAMED(KSNAME_Pin)


typedef enum {
    KSPROPERTY_PIN_CINSTANCES,
    KSPROPERTY_PIN_CTYPES,
    KSPROPERTY_PIN_DATAFLOW,
    KSPROPERTY_PIN_DATARANGES,
    KSPROPERTY_PIN_DATAINTERSECTION,
    KSPROPERTY_PIN_INTERFACES,
    KSPROPERTY_PIN_MEDIUMS,
    KSPROPERTY_PIN_COMMUNICATION,
    KSPROPERTY_PIN_GLOBALCINSTANCES,
    KSPROPERTY_PIN_NECESSARYINSTANCES,
    KSPROPERTY_PIN_PHYSICALCONNECTION,
    KSPROPERTY_PIN_CATEGORY,
    KSPROPERTY_PIN_NAME,
    KSPROPERTY_PIN_CONSTRAINEDDATARANGES,
    KSPROPERTY_PIN_PROPOSEDATAFORMAT
} KSPROPERTY_PIN;

typedef struct {
    KSPROPERTY      Property;
    ULONG           PinId;
    ULONG           Reserved;
} KSP_PIN, *PKSP_PIN;

#define KSINSTANCE_INDETERMINATE    ((ULONG)-1)

typedef struct {
    ULONG  PossibleCount;
    ULONG  CurrentCount;
} KSPIN_CINSTANCES, *PKSPIN_CINSTANCES;

typedef struct {
    ULONG   Size;
    ULONG   Pin;
    WCHAR   SymbolicLinkName[1];
} KSPIN_PHYSICALCONNECTION, *PKSPIN_PHYSICALCONNECTION;


/* ===============================================================
    Quality
    Properties/Methods/Events
*/

#define KSPROPSETID_Quality \
    0xD16AD380L, 0xAC1A, 0x11CF, 0xA5, 0xD6, 0x28, 0xDB, 0x04, 0xC1, 0x00, 0x00

typedef enum {
    KSPROPERTY_QUALITY_REPORT,
    KSPROPERTY_QUALITY_ERROR
} KSPROPERTY_QUALITY;


/* ===============================================================
    Stream
    Properties/Methods/Events
*/

#define STATIC_KSPROPSETID_Stream\
    0x65aaba60L, 0x98ae, 0x11cf, {0xa1, 0x0d, 0x00, 0x20, 0xaf, 0xd1, 0x56, 0xe4}
DEFINE_GUIDSTRUCT("65aaba60-98ae-11cf-a10d-0020afd156e4", KSPROPSETID_Stream);
#define KSPROPSETID_Stream DEFINE_GUIDNAMED(KSPROPSETID_Stream)

typedef enum {
    KSPROPERTY_STREAM_ALLOCATOR,
    KSPROPERTY_STREAM_QUALITY,
    KSPROPERTY_STREAM_DEGRADATION,
    KSPROPERTY_STREAM_MASTERCLOCK,
    KSPROPERTY_STREAM_TIMEFORMAT,
    KSPROPERTY_STREAM_PRESENTATIONTIME,
    KSPROPERTY_STREAM_PRESENTATIONEXTENT,
    KSPROPERTY_STREAM_FRAMETIME,
    KSPROPERTY_STREAM_RATECAPABILITY,
    KSPROPERTY_STREAM_RATE,
    KSPROPERTY_STREAM_PIPE_ID
} KSPROPERTY_STREAM;

#define DEFINE_KSPROPERTY_ITEM_STREAM_ALLOCATOR(GetHandler, SetHandler)\
    DEFINE_KSPROPERTY_ITEM(\
                           KSPROPERTY_STREAM_ALLOCATOR,\
                           (GetHandler),\
                           sizeof(KSPROPERTY),\
                           sizeof(HANDLE),\
                           (SetHandler),\
                           NULL, 0, NULL, NULL, 0)

#define DEFINE_KSPROPERTY_ITEM_STREAM_QUALITY(Handler)\
    DEFINE_KSPROPERTY_ITEM(\
                           KSPROPERTY_STREAM_QUALITY,\
                           (Handler),\
                           sizeof(KSPROPERTY),\
                           sizeof(KSQUALITY_MANAGER),\
                           NULL, NULL, 0, NULL, NULL, 0)

#define DEFINE_KSPROPERTY_ITEM_STREAM_DEGRADATION(GetHandler, SetHandler)\
    DEFINE_KSPROPERTY_ITEM(\
                           KSPROPERTY_STREAM_DEGRADATION,\
                           (GetHandler),\
                           sizeof(KSPROPERTY),\
                           0,\
                           (SetHandler),\
                           NULL, 0, NULL, NULL, 0)

#define DEFINE_KSPROPERTY_ITEM_STREAM_MASTERCLOCK(GetHandler, SetHandler)\
    DEFINE_KSPROPERTY_ITEM(\
                           KSPROPERTY_STREAM_MASTERCLOCK,\
                           (GetHandler),\
                           sizeof(KSPROPERTY),\
                           sizeof(HANDLE),\
                           (SetHandler),\
                           NULL, 0, NULL, NULL, 0)

#define DEFINE_KSPROPERTY_ITEM_STREAM_TIMEFORMAT(Handler)\
    DEFINE_KSPROPERTY_ITEM(\
                           KSPROPERTY_STREAM_TIMEFORMAT,\
                           (Handler),\
                           sizeof(KSPROPERTY),\
                           sizeof(GUID),\
                           NULL, NULL, 0, NULL, NULL, 0)

#define DEFINE_KSPROPERTY_ITEM_STREAM_PRESENTATIONTIME(GetHandler, SetHandler)\
    DEFINE_KSPROPERTY_ITEM(\
                           KSPROPERTY_STREAM_PRESENTATIONTIME,\
                           (GetHandler),\
                           sizeof(KSPROPERTY),\
                           sizeof(KSTIME),\
                           (SetHandler),\
                           NULL, 0, NULL, NULL, 0)

#define DEFINE_KSPROPERTY_ITEM_STREAM_PRESENTATIONEXTENT(Handler)\
    DEFINE_KSPROPERTY_ITEM(\
                           KSPROPERTY_STREAM_PRESENTATIONEXTENT,\
                           (Handler),\
                           sizeof(KSPROPERTY),\
                           sizeof(LONGLONG),\
                           NULL, NULL, 0, NULL, NULL, 0)

#define DEFINE_KSPROPERTY_ITEM_STREAM_FRAMETIME(Handler)\
    DEFINE_KSPROPERTY_ITEM(\
                           KSPROPERTY_STREAM_FRAMETIME,\
                           (Handler),\
                           sizeof(KSPROPERTY),\
                           sizeof(KSFRAMETIME),\
                           NULL, NULL, 0, NULL, NULL, 0)

#define DEFINE_KSPROPERTY_ITEM_STREAM_RATECAPABILITY(Handler)\
    DEFINE_KSPROPERTY_ITEM(\
                           KSPROPERTY_STREAM_RATECAPABILITY,\
                           (Handler),\
                           sizeof(KSRATE_CAPABILITY),\
                           sizeof(KSRATE),\
                           NULL, NULL, 0, NULL, NULL, 0)

#define DEFINE_KSPROPERTY_ITEM_STREAM_RATE(GetHandler, SetHandler)\
    DEFINE_KSPROPERTY_ITEM(\
                           KSPROPERTY_STREAM_RATE,\
                           (GetHandler),\
                           sizeof(KSPROPERTY),\
                           sizeof(KSRATE),\
                           (SetHandler),\
                           NULL, 0, NULL, NULL, 0)

#define DEFINE_KSPROPERTY_ITEM_STREAM_PIPE_ID(GetHandler, SetHandler)\
    DEFINE_KSPROPERTY_ITEM(\
                           KSPROPERTY_STREAM_PIPE_ID,\
                           (GetHandler),\
                           sizeof(KSPROPERTY),\
                           sizeof(HANDLE),\
                           (SetHandler),\
                           NULL, 0, NULL, NULL, 0)

/* ===============================================================
    StreamAllocator
    Properties/Methods/Events
*/

#define STATIC_KSPROPSETID_StreamAllocator\
    0xcf6e4342L, 0xec87, 0x11cf, {0xa1, 0x30, 0x00, 0x20, 0xaf, 0xd1, 0x56, 0xe4}
DEFINE_GUIDSTRUCT("cf6e4342-ec87-11cf-a130-0020afd156e4", KSPROPSETID_StreamAllocator);
#define KSPROPSETID_StreamAllocator DEFINE_GUIDNAMED(KSPROPSETID_StreamAllocator)

typedef enum {
    KSPROPERTY_STREAMALLOCATOR_FUNCTIONTABLE,
    KSPROPERTY_STREAMALLOCATOR_STATUS
} KSPROPERTY_STREAMALLOCATOR;

#define KSMETHODSETID_StreamAllocator \
    0xcf6e4341L, 0xec87, 0x11cf, {0xa1, 0x30, 0x00, 0x20, 0xaf, 0xd1, 0x56, 0xe4}

typedef enum {
    KSMETHOD_STREAMALLOCATOR_ALLOC,
    KSMETHOD_STREAMALLOCATOR_FREE
} KSMETHOD_STREAMALLOCATOR;


#define KSEVENTSETID_StreamAllocator

typedef enum {
    KSEVENT_STREAMALLOCATOR_INTERNAL_FREEFRAME,
    KSEVENT_STREAMALLOCATOR_FREEFRAME
} KSEVENT_STREAMALLOCATOR;


/* ===============================================================
    StreamInterface
    Properties/Methods/Events
*/

#define KSPROPSETID_StreamInterface \
    0x1fdd8ee1L, 0x9cd3, 0x11d0, 0x82, 0xaa, 0x00, 0x00, 0xf8, 0x22, 0xfe, 0x8a

typedef enum {
    KSPROPERTY_STREAMINTERFACE_HEADERSIZE
} KSPROPERTY_STREAMINTERFACE;


/* ===============================================================
    Topology
    Properties/Methods/Events
*/

#define STATIC_KSPROPSETID_Topology\
    0x720D4AC0L, 0x7533, 0x11D0, {0xA5, 0xD6, 0x28, 0xDB, 0x04, 0xC1, 0x00, 0x00}
DEFINE_GUIDSTRUCT("720D4AC0-7533-11D0-A5D6-28DB04C10000", KSPROPSETID_Topology);
#define KSPROPSETID_Topology DEFINE_GUIDNAMED(KSPROPSETID_Topology)

typedef enum {
    KSPROPERTY_TOPOLOGY_CATEGORIES,
    KSPROPERTY_TOPOLOGY_NODES,
    KSPROPERTY_TOPOLOGY_CONNECTIONS,
    KSPROPERTY_TOPOLOGY_NAME
} KSPROPERTY_TOPOLOGY;

/* ===============================================================
    Property Sets for audio drivers - TODO
*/

#define STATIC_KSPROPTYPESETID_General \
    0x97E99BA0L, 0xBDEA, 0x11CF, {0xA5, 0xD6, 0x28, 0xDB, 0x04, 0xC1, 0x00, 0x00}
DEFINE_GUIDSTRUCT("97E99BA0-BDEA-11CF-A5D6-28DB04C10000", KSPROPTYPESETID_General);
#define KSPROPTYPESETID_General DEFINE_GUIDNAMED(KSPROPTYPESETID_General)

/*
    KSPROPERTY_AC3_ALTERNATE_AUDIO
    KSPROPERTY_AC3_BIT_STREAM_MODE
    KSPROPERTY_AC3_DIALOGUE_LEVEL
    KSPROPERTY_AC3_DOWNMIX
    KSPROPERTY_AC3_ERROR_CONCEALMENT
    KSPROPERTY_AC3_LANGUAGE_CODE
    KSPROPERTY_AC3_ROOM_TYPE
*/

#define KSPROPSETID_Acoustic_Echo_Cancel
/*
    KSPROPERTY_AEC_MODE
    KSPROPERTY_AEC_NOISE_FILL_ENABLE
    KSPROPERTY_AEC_STATUS
*/

/*
    KSPROPERTY_AUDIO_3D_INTERFACE
    KSPROPERTY_AUDIO_AGC
    KSPROPERTY_AUDIO_ALGORITHM_INSTANCE
    KSPROPERTY_AUDIO_BASS
    KSPROPERTY_AUDIO_BASS_BOOST
    KSPROPERTY_AUDIO_CHANNEL_CONFIG
    KSPROPERTY_AUDIO_CHORUS_LEVEL
    KSPROPERTY_AUDIO_COPY_PROTECTION
    KSPROPERTY_AUDIO_CPU_RESOURCES
    KSPROPERTY_AUDIO_DELAY
    KSPROPERTY_AUDIO_DEMUX_DEST
    KSPROPERTY_AUDIO_DEV_SPECIFIC
    KSPROPERTY_AUDIO_DYNAMIC_RANGE
    KSPROPERTY_AUDIO_DYNAMIC_SAMPLING_RATE
    KSPROPERTY_AUDIO_EQ_BANDS
    KSPROPERTY_AUDIO_EQ_LEVEL
    KSPROPERTY_AUDIO_FILTER_STATE
    KSPROPERTY_AUDIO_LATENCY
    KSPROPERTY_AUDIO_LOUDNESS
    KSPROPERTY_AUDIO_MANUFACTURE_GUID
    KSPROPERTY_AUDIO_MID
    KSPROPERTY_AUDIO_MIX_LEVEL_CAPS
    KSPROPERTY_AUDIO_MIX_LEVEL_TABLE
    KSPROPERTY_AUDIO_MUTE
    KSPROPERTY_AUDIO_MUX_SOURCE
    KSPROPERTY_AUDIO_NUM_EQ_BANDS
    KSPROPERTY_AUDIO_PEAKMETER
    KSPROPERTY_AUDIO_POSITION
    KSPROPERTY_AUDIO_PREFERRED_STATUS
    KSPROPERTY_AUDIO_PRODUCT_GUID
    KSPROPERTY_AUDIO_QUALITY
    KSPROPERTY_AUDIO_REVERB_LEVEL
    KSPROPERTY_AUDIO_SAMPLING_RATE
    KSPROPERTY_AUDIO_STEREO_ENHANCE
    KSPROPERTY_AUDIO_STEREO_SPEAKER_GEOMETRY
    KSPROPERTY_AUDIO_SURROUND_ENCODE
    KSPROPERTY_AUDIO_TREBLE
    KSPROPERTY_AUDIO_VOLUMELEVEL
    KSPROPERTY_AUDIO_WIDE_MODE
    KSPROPERTY_AUDIO_WIDENESS
*/

#define KSPROPSETID_AudioGfx
/*
    KSPROPERTY_AUDIOGFX_CAPTURETARGETDEVICEID
    KSPROPERTY_AUDIOGFX_RENDERTARGETDEVICEID
*/

#define KSPROPSETID_DirectSound3DBuffer
/*
    KSPROPERTY_DIRECTSOUND3DBUFFER_ALL
    KSPROPERTY_DIRECTSOUND3DBUFFER_CONEANGLES
    KSPROPERTY_DIRECTSOUND3DBUFFER_CONEORIENTATION
    KSPROPERTY_DIRECTSOUND3DBUFFER_CONEOUTSIDEVOLUME
    KSPROPERTY_DIRECTSOUND3DBUFFER_MAXDISTANCE
    KSPROPERTY_DIRECTSOUND3DBUFFER_MINDISTANCE
    KSPROPERTY_DIRECTSOUND3DBUFFER_MODE
    KSPROPERTY_DIRECTSOUND3DBUFFER_POSITION
    KSPROPERTY_DIRECTSOUND3DBUFFER_VELOCITY
*/

#define KSPROPSETID_DirectSound3DListener
/*
    KSPROPERTY_DIRECTSOUND3DLISTENER_ALL
    KSPROPERTY_DIRECTSOUND3DLISTENER_ALLOCATION
    KSPROPERTY_DIRECTSOUND3DLISTENER_BATCH
    KSPROPERTY_DIRECTSOUND3DLISTENER_DISTANCEFACTOR
    KSPROPERTY_DIRECTSOUND3DLISTENER_DOPPLERFACTOR
    KSPROPERTY_DIRECTSOUND3DLISTENER_ORIENTATION
    KSPROPERTY_DIRECTSOUND3DLISTENER_POSITION
    KSPROPERTY_DIRECTSOUND3DLISTENER_ROLLOFFFACTOR
    KSPROPERTY_DIRECTSOUND3DLISTENER_VELOCITY
*/

#define KSPROPSETID_Hrtf3d
/*
    KSPROPERTY_HRTF3D_FILTER_FORMAT
    KSPROPERTY_HRTF3D_INITIALIZE
    KSPROPERTY_HRTF3D_PARAMS
*/

#define KSPROPSETID_Itd3d
/*
    KSPROPERTY_ITD3D_PARAMS
*/

#define KSPROPSETID_TopologyNode
/*
    KSPROPERTY_TOPOLOGYNODE_ENABLE
    KSPROPERTY_TOPOLOGYNODE_RESET
*/


/* ===============================================================
    Node Types
*/
/*
    KSNODETYPE_3D_EFFECTS
    KSNODETYPE_ACOUSTIC_ECHO_CANCEL
    KSNODETYPE_ADC
    KSNODETYPE_AGC
    KSNODETYPE_CHORUS
    KSNODETYPE_DAC
    KSNODETYPE_DELAY
    KSNODETYPE_DEMUX
    KSNODETYPE_DEV_SPECIFIC
    KSNODETYPE_DMSYNTH
    KSNODETYPE_DMSYNTH_CAPS
    KSNODETYPE_DRM_DESCRAMBLE
    KSNODETYPE_EQUALIZER
    KSNODETYPE_LOUDNESS
    KSNODETYPE_MUTE
    KSNODETYPE_MUX
    KSNODETYPE_PEAKMETER
    KSNODETYPE_PROLOGIC_DECODER
    KSNODETYPE_PROLOGIC_ENCODER
    KSNODETYPE_REVERB
    KSNODETYPE_SRC
    KSNODETYPE_STEREO_ENHANCE
    KSNODETYPE_STEREO_WIDE
    KSNODETYPE_SUM
    KSNODETYPE_SUPERMIX
    KSNODETYPE_SWMIDI
    KSNODETYPE_SWSYNTH
    KSNODETYPE_SYNTHESIZER
    KSNODETYPE_TONE
    KSNODETYPE_VOLUME
*/


typedef PVOID   KSDEVICE_HEADER,
        KSOBJECT_HEADER,
        KSOBJECT_BAG;




/* ===============================================================
    Method Types
*/

#define KSMETHOD_TYPE_NONE          0x00000000
#define KSMETHOD_TYPE_READ          0x00000001
#define KSMETHOD_TYPE_WRITE         0x00000002
#define KSMETHOD_TYPE_MODIFY        0x00000003
#define KSMETHOD_TYPE_SOURCE        0x00000004
#define KSMETHOD_TYPE_SEND          0x00000001
#define KSMETHOD_TYPE_SETSUPPORT    0x00000100
#define KSMETHOD_TYPE_BASICSUPPORT  0x00000200


/* ===============================================================
    Property Types
*/

#define KSPROPERTY_TYPE_GET             0x00000001
#define KSPROPERTY_TYPE_SET             0x00000002
#define KSPROPERTY_TYPE_SETSUPPORT      0x00000100
#define KSPROPERTY_TYPE_BASICSUPPORT    0x00000200
#define KSPROPERTY_TYPE_RELATIONS       0x00000400
#define KSPROPERTY_TYPE_SERIALIZESET    0x00000800
#define KSPROPERTY_TYPE_UNSERIALIZESET  0x00001000
#define KSPROPERTY_TYPE_SERIALIZERAW    0x00002000
#define KSPROPERTY_TYPE_UNSERIALIZERAW  0x00004000
#define KSPROPERTY_TYPE_SERIALIZESIZE   0x00008000
#define KSPROPERTY_TYPE_DEFAULT_VALUES  0x00010000


/* ===============================================================
    Topology Methods/Properties
*/

#define KSMETHOD_TYPE_TOPOLOGY          0x10000000
#define KSPROPERTY_TYPE_TOPOLOGY        0x10000000

/*
#define DEFINE_KS_GUID(GA,GB,GC,GD,GE,GF,GG,GH,GI,GJ,GK) \
    DEFINE_GUID(??, 0x#GA#L, 0xGB, 0xGC, 0xGD, 0xGE, 0xGF, 0xGG, 0xGH, 0xGI, 0xGJ, 0xGK) \
    "GA-GB-GC-GDGE-GFGGGHGIGJGK"
*/

/* ===============================================================
    KS Category GUIDs

    BRIDGE - 0x085AFF00L, 0x62CE, 0x11CF, 0xA5, 0xD6, 0x28, 0xDB, 0x04, 0xC1, 0x00, 0x00
    CAPTURE - 0x65E8773DL, 0x8F56, 0x11D0, 0xA3, 0xB9, 0x00, 0xA0, 0xC9, 0x22, 0x31, 0x96
    RENDER - 0x65E8773EL, 0x8F56, 0x11D0, 0xA3, 0xB9, 0x00, 0xA0, 0xC9, 0x22, 0x31, 0x96
    MIXER - 0xAD809C00L, 0x7B88, 0x11D0, 0xA5, 0xD6, 0x28, 0xDB, 0x04, 0xC1, 0x00, 0x00
    SPLITTER - 0x0A4252A0L, 0x7E70, 0x11D0, 0xA5, 0xD6, 0x28, 0xDB, 0x04, 0xC1, 0x00, 0x00
    DATACOMPRESSOR - 0x1E84C900L, 0x7E70, 0x11D0, 0xA5, 0xD6, 0x28, 0xDB, 0x04, 0xC1, 0x00, 0x00
    DATADECOMPRESSOR - 0x2721AE20L, 0x7E70, 0x11D0, 0xA5, 0xD6, 0x28, 0xDB, 0x04, 0xC1, 0x00, 0x00
    DATATRANSFORM - 0x2EB07EA0L, 0x7E70, 0x11D0, 0xA5, 0xD6, 0x28, 0xDB, 0x04, 0xC1, 0x00, 0x00
    COMMUNICATIONSTRANSFORM - 0xCF1DDA2CL, 0x9743, 0x11D0, 0xA3, 0xEE, 0x00, 0xA0, 0xC9, 0x22, 0x31, 0x96
    INTERFACETRANSFORM - 0xCF1DDA2DL, 0x9743, 0x11D0, 0xA3, 0xEE, 0x00, 0xA0, 0xC9, 0x22, 0x31, 0x96
    MEDIUMTRANSFORM - 0xCF1DDA2EL, 0x9743, 0x11D0, 0xA3, 0xEE, 0x00, 0xA0, 0xC9, 0x22, 0x31, 0x96
    FILESYSTEM - 0x760FED5EL, 0x9357, 0x11D0, 0xA3, 0xCC, 0x00, 0xA0, 0xC9, 0x22, 0x31, 0x96
    CLOCK - 0x53172480L, 0x4791, 0x11D0, 0xA5, 0xD6, 0x28, 0xDB, 0x04, 0xC1, 0x00, 0x00
    PROXY - 0x97EBAACAL, 0x95BD, 0x11D0, 0xA3, 0xEA, 0x00, 0xA0, 0xC9, 0x22, 0x31, 0x96
    QUALITY - 0x97EBAACBL, 0x95BD, 0x11D0, 0xA3, 0xEA, 0x00, 0xA0, 0xC9, 0x22, 0x31, 0x96
*/

/* ===============================================================
    KSNAME GUIDs (defined also as KSSTRING_Xxx L"{...}"

    Filter - 0x9b365890L, 0x165f, 0x11d0, 0xa1, 0x95, 0x00, 0x20, 0xaf, 0xd1, 0x56, 0xe4
    Pin - 0x146F1A80L, 0x4791, 0x11D0, 0xA5, 0xD6, 0x28, 0xDB, 0x04, 0xC1, 0x00, 0x00
    Clock - 0x53172480L, 0x4791, 0x11D0, 0xA5, 0xD6, 0x28, 0xDB, 0x04, 0xC1, 0x00, 0x00
    Allocator - 0x642F5D00L, 0x4791, 0x11D0, 0xA5, 0xD6, 0x28, 0xDB, 0x04, 0xC1, 0x00, 0x00
    TopologyNode - 0x0621061AL, 0xEE75, 0x11D0, 0xB9, 0x15, 0x00, 0xA0, 0xC9, 0x22, 0x31, 0x96
*/

/* ===============================================================
    Interface GUIDs

    Standard - 0x1A8766A0L, 0x62CE, 0x11CF, 0xA5, 0xD6, 0x28, 0xDB, 0x04, 0xC1, 0x00, 0x00
    FileIo - 0x8C6F932CL, 0xE771, 0x11D0, 0xB8, 0xFF, 0x00, 0xA0, 0xC9, 0x22, 0x31, 0x96
*/

/* ===============================================================
    Medium Type GUIDs

    Standard - 0x4747B320L, 0x62CE, 0x11CF, 0xA5, 0xD6, 0x28, 0xDB, 0x04, 0xC1, 0x00, 0x00
*/

/* ===============================================================
    Property Set GUIDs

    General - 0x1464EDA5L, 0x6A8F, 0x11D1, 0x9A, 0xA7, 0x00, 0xA0, 0xC9, 0x22, 0x31, 0x96
    StreamIo - 0x65D003CAL, 0x1523, 0x11D2, 0xB2, 0x7A, 0x00, 0xA0, 0xC9, 0x22, 0x31, 0x96
    MediaSeeking - 0xEE904F0CL, 0xD09B, 0x11D0, 0xAB, 0xE9, 0x00, 0xA0, 0xC9, 0x22, 0x31, 0x96
    Topology - 0x720D4AC0L, 0x7533, 0x11D0, 0xA5, 0xD6, 0x28, 0xDB, 0x04, 0xC1, 0x00, 0x00
    GM - 0xAF627536L, 0xE719, 0x11D2, 0x8A, 0x1D, 0x00, 0x60, 0x97, 0xD2, 0xDF, 0x5D
    Quality - 0xD16AD380L, 0xAC1A, 0x11CF, 0xA5, 0xD6, 0x28, 0xDB, 0x04, 0xC1, 0x00, 0x00
    Connection - 0x1D58C920L, 0xAC9B, 0x11CF, 0xA5, 0xD6, 0x28, 0xDB, 0x04, 0xC1, 0x00, 0x00
*/

/* ===============================================================
    StreamAllocator Sets

    Event set - 0x75d95571L, 0x073c, 0x11d0, 0xa1, 0x61, 0x00, 0x20, 0xaf, 0xd1, 0x56, 0xe4
    Method set - 0xcf6e4341L, 0xec87, 0x11cf, 0xa1, 0x30, 0x00, 0x20, 0xaf, 0xd1, 0x56, 0xe4
    Property set - 0xcf6e4342L, 0xec87, 0x11cf, 0xa1, 0x30, 0x00, 0x20, 0xaf, 0xd1, 0x56, 0xe4
*/

/* ===============================================================
    StreamInterface Sets

    Property set - 0x1fdd8ee1L, 0x9cd3, 0x11d0, 0x82, 0xaa, 0x00, 0x00, 0xf8, 0x22, 0xfe, 0x8a
*/

/* ===============================================================
    Clock Sets

    Property set - 0xDF12A4C0L, 0xAC17, 0x11CF, 0xA5, 0xD6, 0x28, 0xDB, 0x04, 0xC1, 0x00, 0x00
    Event sets - 0x364D8E20L, 0x62C7, 0x11CF, 0xA5, 0xD6, 0x28, 0xDB, 0x04, 0xC1, 0x00, 0x00
*/

/* ===============================================================
    Connection Sets

    Event set - 0x7f4bcbe0L, 0x9ea5, 0x11cf, 0xa5, 0xd6, 0x28, 0xdb, 0x04, 0xc1, 0x00, 0x00
*/

/* ===============================================================
    Time Format GUIDs

    KSTIME_FORMAT_NONE  (null guid)
    FRAME - 0x7b785570L, 0x8c82, 0x11cf, 0xbc, 0x0c, 0x00, 0xaa, 0x00, 0xac, 0x74, 0xf6
    BYTE - 0x7b785571L, 0x8c82, 0x11cf, 0xbc, 0x0c, 0x00, 0xaa, 0x00, 0xac, 0x74, 0xf6
    SAMPLE - 0x7b785572L, 0x8c82, 0x11cf, 0xbc, 0x0c, 0x00, 0xaa, 0x00, 0xac, 0x74, 0xf6
    FIELD - 0x7b785573L, 0x8c82, 0x11cf, 0xbc, 0x0c, 0x00, 0xaa, 0x00, 0xac, 0x74, 0xf6
    MEDIA_TIME - 0x7b785574L, 0x8c82, 0x11cf, 0xbc, 0x0c, 0x00, 0xaa, 0x00, 0xac, 0x74, 0xf6
*/

/* ===============================================================
    Media Type GUIDs

    NULL
    Stream -
    None -

    TODO ...
*/

#define STATIC_KSDATAFORMAT_SPECIFIER_NONE\
    0x0F6417D6L, 0xC318, 0x11D0, {0xA4, 0x3F, 0x00, 0xA0, 0xC9, 0x22, 0x31, 0x96}
DEFINE_GUIDSTRUCT("0F6417D6-C318-11D0-A43F-00A0C9223196", KSDATAFORMAT_SPECIFIER_NONE);
#define KSDATAFORMAT_SPECIFIER_NONE DEFINE_GUIDNAMED(KSDATAFORMAT_SPECIFIER_NONE)


/* ===============================================================
    KSMEMORY_TYPE_xxx

    WILDCARD, DONT_CARE = NULL
    SYSTEM - 0x091bb638L, 0x603f, 0x11d1, 0xb0, 0x67, 0x00, 0xa0, 0xc9, 0x06, 0x28, 0x02
    USER - 0x8cb0fc28L, 0x7893, 0x11d1, 0xb0, 0x69, 0x00, 0xa0, 0xc9, 0x06, 0x28, 0x02
    KERNEL_PAGED - 0xd833f8f8L, 0x7894, 0x11d1, 0xb0, 0x69, 0x00, 0xa0, 0xc9, 0x06, 0x28, 0x02
    KERNEL_NONPAGED - 0x4a6d5fc4L, 0x7895, 0x11d1, 0xb0, 0x69, 0x00, 0xa0, 0xc9, 0x06, 0x28, 0x02
    DEVICE_UNKNOWN - 0x091bb639L, 0x603f, 0x11d1, 0xb0, 0x67, 0x00, 0xa0, 0xc9, 0x06, 0x28, 0x02
*/

/* ===============================================================
    Enums
    (values have been checked)
*/

#ifndef _MSC_VER

#define DEFINE_KSPROPERTY_ITEM(PropertyId, GetHandler,\
                               MinProperty,\
                               MinData,\
                               SetHandler,\
                               Values, RelationsCount, Relations, SupportHandler,\
                               SerializedSize)\
{\
    PropertyId, {(PFNKSHANDLER)GetHandler}, MinProperty, MinData,\
    {(PFNKSHANDLER)SetHandler},\
    (PKSPROPERTY_VALUES)Values, RelationsCount, (PKSPROPERTY)Relations,\
    (PFNKSHANDLER)SupportHandler, (ULONG)SerializedSize\
}

#else

#define DEFINE_KSPROPERTY_ITEM(PropertyId, GetHandler,\
                               MinProperty,\
                               MinData,\
                               SetHandler,\
                               Values, RelationsCount, Relations, SupportHandler,\
                               SerializedSize)\
{\
    PropertyId, (PFNKSHANDLER)GetHandler, MinProperty, MinData,\
    (PFNKSHANDLER)SetHandler,\
    (PKSPROPERTY_VALUES)Values, RelationsCount, (PKSPROPERTY)Relations,\
    (PFNKSHANDLER)SupportHandler, (ULONG)SerializedSize\
}

#endif


typedef enum {
    KsObjectTypeDevice,
    KsObjectTypeFilterFactory,
    KsObjectTypeFilter,
    KsObjectTypePin
} KSOBJECTTYPE;

typedef enum {
    KSSTATE_STOP,
    KSSTATE_ACQUIRE,
    KSSTATE_PAUSE,
    KSSTATE_RUN
} KSSTATE, *PKSSTATE;

typedef enum {
    KSTARGET_STATE_DISABLED,
    KSTARGET_STATE_ENABLED
} KSTARGET_STATE;

typedef enum {
    KSRESET_BEGIN,
    KSRESET_END
} KSRESET;

typedef enum {
    KSEVENTS_NONE,
    KSEVENTS_SPINLOCK,
    KSEVENTS_MUTEX,
    KSEVENTS_FMUTEX,
    KSEVENTS_FMUTEXUNSAFE,
    KSEVENTS_INTERRUPT,
    KSEVENTS_ERESOURCE
} KSEVENTS_LOCKTYPE;

typedef enum {
    KSDEGRADE_STANDARD_SIMPLE,
    KSDEGRADE_STANDARD_QUALITY,
    KSDEGRADE_STANDARD_COMPUTATION,
    KSDEGRADE_STANDARD_SKIP
} KSDEGRADE_STANDARD;

typedef enum {
    KSPIN_DATAFLOW_IN = 1,
    KSPIN_DATAFLOW_OUT
} KSPIN_DATAFLOW, *PKSPIN_DATAFLOW;

typedef enum {
    KSPIN_COMMUNICATION_NONE,
    KSPIN_COMMUNICATION_SINK,
    KSPIN_COMMUNICATION_SOURCE,
    KSPIN_COMMUNICATION_BOTH,
    KSPIN_COMMUNICATION_BRIDGE
} KSPIN_COMMUNICATION, *PKSPIN_COMMUNICATION;

typedef enum {
    KsListEntryTail,
    KsListEntryHead
} KSLIST_ENTRY_LOCATION;

typedef enum {
    KsStackCopyToNewLocation,
    KsStackReuseCurrentLocation,
    KsStackUseNewLocation
} KSSTACK_USE;

typedef enum {
    KsAcquireOnly,
    KsAcquireAndRemove,
    KsAcquireOnlySingleItem,
    KsAcquireAndRemoveOnlySingleItem
} KSIRP_REMOVAL_OPERATION;

typedef enum {
    KsInvokeOnSuccess = 1,
    KsInvokeOnError = 2,
    KsInvokeOnCancel = 4
} KSCOMPLETION_INVOCATION;


#if defined(_NTDDK_)
/* MOVE ME */
typedef NTSTATUS(NTAPI *PFNKSCONTEXT_DISPATCH)(
    IN PVOID Context,
    IN PIRP Irp);
#endif

#if defined(_NTDDK_) && !defined(__wtypes_h__)
enum VARENUM {
    VT_EMPTY = 0,
    VT_NULL = 1,
    VT_I2 = 2,
    VT_I4 = 3,
    VT_R4 = 4,
    VT_R8 = 5,
    VT_CY = 6,
    VT_DATE = 7,
    VT_BSTR = 8,
    VT_DISPATCH = 9,
    VT_ERROR = 10,
    VT_BOOL = 11,
    VT_VARIANT = 12,
    VT_UNKNOWN = 13,
    VT_DECIMAL = 14,
    VT_I1 = 16,
    VT_UI1 = 17,
    VT_UI2 = 18,
    VT_UI4 = 19,
    VT_I8 = 20,
    VT_UI8 = 21,
    VT_INT = 22,
    VT_UINT = 23,
    VT_VOID = 24,
    VT_HRESULT  = 25,
    VT_PTR = 26,
    VT_SAFEARRAY = 27,
    VT_CARRAY = 28,
    VT_USERDEFINED = 29,
    VT_LPSTR = 30,
    VT_LPWSTR = 31,
    VT_FILETIME = 64,
    VT_BLOB = 65,
    VT_STREAM = 66,
    VT_STORAGE = 67,
    VT_STREAMED_OBJECT = 68,
    VT_STORED_OBJECT = 69,
    VT_BLOB_OBJECT = 70,
    VT_CF = 71,
    VT_CLSID = 72,
    VT_VECTOR = 0x1000,
    VT_ARRAY = 0x2000,
    VT_BYREF = 0x4000,
    VT_RESERVED = 0x8000,
    VT_ILLEGAL = 0xffff,
    VT_ILLEGALMASKED = 0xfff,
    VT_TYPEMASK = 0xfff
};
#endif

#define STATIC_KSDATAFORMAT_TYPE_WILDCARD       STATIC_GUID_NULL
#define KSDATAFORMAT_TYPE_WILDCARD              GUID_NULL

#define STATIC_KSDATAFORMAT_SUBTYPE_WILDCARD    STATIC_GUID_NULL
#define KSDATAFORMAT_SUBTYPE_WILDCARD           GUID_NULL

#define STATIC_KSDATAFORMAT_SPECIFIER_WILDCARD  STATIC_GUID_NULL
#define KSDATAFORMAT_SPECIFIER_WILDCARD         GUID_NULL

/* ===============================================================
    Framing
*/

typedef struct {
    ULONG   MinFrameSize;
    ULONG   MaxFrameSize;
    ULONG   Stepping;
} KS_FRAMING_RANGE, *PKS_FRAMING_RANGE;

typedef struct {
    KS_FRAMING_RANGE  Range;
    ULONG             InPlaceWeight;
    ULONG             NotInPlaceWeight;
} KS_FRAMING_RANGE_WEIGHTED, *PKS_FRAMING_RANGE_WEIGHTED;

typedef struct {
    GUID                        MemoryType;
    GUID                        BusType;
    ULONG                       MemoryFlags;
    ULONG                       BusFlags;
    ULONG                       Flags;
    ULONG                       Frames;
    ULONG                       FileAlignment;
    ULONG                       MemoryTypeWeight;
    KS_FRAMING_RANGE            PhysicalRange;
    KS_FRAMING_RANGE_WEIGHTED   FramingRange;
} KS_FRAMING_ITEM, *PKS_FRAMING_ITEM;

typedef struct {
    ULONG   RatioNumerator;
    ULONG   RatioDenominator;
    ULONG   RatioConstantMargin;
} KS_COMPRESSION, *PKS_COMPRESSION;


/* ===============================================================
    Priorities
*/

#define KSPRIORITY_LOW          0x00000001
#define KSPRIORITY_NORMAL       0x40000000
#define KSPRIORITY_HIGH         0x80000000
#define KSPRIORITY_EXCLUSIVE    0xFFFFFFFF

typedef struct {
    ULONG PriorityClass;
    ULONG PrioritySubClass;
} KSPRIORITY, *PKSPRIORITY;


/* ===============================================================
    Dispatch Table
    http://www.osronline.com/DDKx/stream/ks-struct_494j.htm
*/
#if defined(_NTDDK_)
typedef struct {
    PDRIVER_DISPATCH DeviceIoControl;
    PDRIVER_DISPATCH Read;
    PDRIVER_DISPATCH Write;
    PDRIVER_DISPATCH Flush;
    PDRIVER_DISPATCH Close;
    PDRIVER_DISPATCH QuerySecurity;
    PDRIVER_DISPATCH SetSecurity;
    PFAST_IO_DEVICE_CONTROL FastDeviceIoControl;
    PFAST_IO_READ FastRead;
    PFAST_IO_WRITE FastWrite;
} KSDISPATCH_TABLE, *PKSDISPATCH_TABLE;


#define KSCREATE_ITEM_IRP_STORAGE(Irp)      (*(PKSOBJECT_CREATE_ITEM*)&(Irp)->Tail.Overlay.DriverContext[0])
#define KSEVENT_SET_IRP_STORAGE(Irp)        (*(const KSEVENT_SET**)&(Irp)->Tail.Overlay.DriverContext[0])
#define KSEVENT_ITEM_IRP_STORAGE(Irp)       (*(const KSEVENT_ITEM**)&(Irp)->Tail.Overlay.DriverContext[3])
#define KSEVENT_ENTRY_IRP_STORAGE(Irp)      (*(PKSEVENT_ENTRY*)&(Irp)->Tail.Overlay.DriverContext[0])
#define KSMETHOD_SET_IRP_STORAGE(Irp)       (*(const KSMETHOD_SET**)&(Irp)->Tail.Overlay.DriverContext[0])
#define KSMETHOD_ITEM_IRP_STORAGE(Irp)      (*(const KSMETHOD_ITEM**)&(Irp)->Tail.Overlay.DriverContext[3])
#define KSMETHOD_TYPE_IRP_STORAGE(Irp)      (*(ULONG_PTR*)(&(Irp)->Tail.Overlay.DriverContext[2]))
#define KSQUEUE_SPINLOCK_IRP_STORAGE(Irp)   (*(PKSPIN_LOCK*)&(Irp)->Tail.Overlay.DriverContext[1])
#define KSPROPERTY_SET_IRP_STORAGE(Irp)     (*(const KSPROPERTY_SET**)&(Irp)->Tail.Overlay.DriverContext[0])
#define KSPROPERTY_ITEM_IRP_STORAGE(Irp)    (*(const KSPROPERTY_ITEM**)&(Irp)->Tail.Overlay.DriverContext[3])
#define KSPROPERTY_ATTRIBUTES_IRP_STORAGE(Irp) (*(PKSATTRIBUTE_LIST*)&(Irp)->Tail.Overlay.DriverContext[2])

typedef
VOID
(NTAPI *PFNREFERENCEDEVICEOBJECT)(
    IN PVOID Context
);

typedef
VOID
(NTAPI *PFNDEREFERENCEDEVICEOBJECT)(
    IN PVOID Context
);

typedef
NTSTATUS
(NTAPI *PFNQUERYREFERENCESTRING)(
    IN PVOID Context,
    IN OUT PWCHAR *String
);

typedef struct {
    INTERFACE                   Interface;
    PFNREFERENCEDEVICEOBJECT    ReferenceDeviceObject;
    PFNDEREFERENCEDEVICEOBJECT  DereferenceDeviceObject;
    PFNQUERYREFERENCESTRING     QueryReferenceString;
} BUS_INTERFACE_REFERENCE, *PBUS_INTERFACE_REFERENCE;

typedef struct {
    KDPC            Dpc;
    ULONG           ReferenceCount;
    KSPIN_LOCK      AccessLock;
} KSDPC_ITEM, *PKSDPC_ITEM;

typedef struct {
    KSDPC_ITEM          DpcItem;
    LIST_ENTRY          BufferList;
} KSBUFFER_ITEM, *PKSBUFFER_ITEM;

#endif

typedef struct {
    GUID    Manufacturer;
    GUID    Product;
    GUID    Component;
    GUID    Name;
    ULONG   Version;
    ULONG   Revision;
} KSCOMPONENTID, *PKSCOMPONENTID;

/* ===============================================================
    Properties
*/

typedef struct {
    GUID            PropertySet;
    ULONG           Count;
} KSPROPERTY_SERIALHDR, *PKSPROPERTY_SERIALHDR;

typedef struct {
    KSIDENTIFIER    PropTypeSet;
    ULONG           Id;
    ULONG           PropertyLength;
} KSPROPERTY_SERIAL, *PKSPROPERTY_SERIAL;


typedef union {
    struct {
        LONG    SignedMinimum;
        LONG    SignedMaximum;

#if defined( _KS_NO_ANONYMOUS_STRUCTURES_ )
    } _SIGNED;
#else
    };
#endif

    struct {
        ULONG   UnsignedMinimum;
        ULONG   UnsignedMaximum;
#if defined( _KS_NO_ANONYMOUS_STRUCTURES_ )
    } _UNSIGNED;
#else
    };
#endif

} KSPROPERTY_BOUNDS_LONG, *PKSPROPERTY_BOUNDS_LONG;

typedef union {
    struct {
        LONGLONG    SignedMinimum;
        LONGLONG    SignedMaximum;
#if defined( _KS_NO_ANONYMOUS_STRUCTURES_ )
    } _SIGNED64;
#else
    };
#endif

    struct {
#if defined(_NTDDK_)
        ULONGLONG   UnsignedMinimum;
        ULONGLONG   UnsignedMaximum;
#else
        DWORDLONG   UnsignedMinimum;
        DWORDLONG   UnsignedMaximum;
#endif
#if defined( _KS_NO_ANONYMOUS_STRUCTURES_ )
    } _UNSIGNED64;
#else
    };
#endif
} KSPROPERTY_BOUNDS_LONGLONG, *PKSPROPERTY_BOUNDS_LONGLONG;

typedef struct {
    ULONG           AccessFlags;
    ULONG           DescriptionSize;
    KSIDENTIFIER    PropTypeSet;
    ULONG           MembersListCount;
    ULONG           Reserved;
} KSPROPERTY_DESCRIPTION, *PKSPROPERTY_DESCRIPTION;

typedef struct {
    ULONG   MembersFlags;
    ULONG   MembersSize;
    ULONG   MembersCount;
    ULONG   Flags;
} KSPROPERTY_MEMBERSHEADER, *PKSPROPERTY_MEMBERSHEADER;

typedef struct {
    KSPROPERTY_MEMBERSHEADER    MembersHeader;
    const VOID*                 Members;
} KSPROPERTY_MEMBERSLIST, *PKSPROPERTY_MEMBERSLIST;

#define KSPROPERTY_MEMBER_RANGES            0x00000001
#define KSPROPERTY_MEMBER_STEPPEDRANGES     0x00000002
#define KSPROPERTY_MEMBER_VALUES            0x00000003

#define KSPROPERTY_MEMBER_FLAG_DEFAULT                      0x00000001
#if (NTDDI_VERSION >= NTDDI_WINXP)
    #define KSPROPERTY_MEMBER_FLAG_BASICSUPPORT_MULTICHANNEL    0x00000002
    #define KSPROPERTY_MEMBER_FLAG_BASICSUPPORT_UNIFORM         0x00000004
#endif


typedef struct {
    KSIDENTIFIER                    PropTypeSet;
    ULONG                           MembersListCount;
    const KSPROPERTY_MEMBERSLIST*   MembersList;
} KSPROPERTY_VALUES, *PKSPROPERTY_VALUES;

#if defined(_NTDDK_)
typedef NTSTATUS(NTAPI *PFNKSHANDLER)(
    IN  PIRP Irp,
    IN  PKSIDENTIFIER Request,
    IN  OUT PVOID Data);

typedef struct {
    ULONG PropertyId;
    union {
        PFNKSHANDLER GetPropertyHandler;
        BOOLEAN GetSupported;
    };
    ULONG MinProperty;
    ULONG MinData;
    union {
        PFNKSHANDLER SetPropertyHandler;
        BOOLEAN SetSupported;
    };
    const KSPROPERTY_VALUES * Values;
    ULONG RelationsCount;
    const KSPROPERTY * Relations;
    PFNKSHANDLER SupportHandler;
    ULONG SerializedSize;
} KSPROPERTY_ITEM, *PKSPROPERTY_ITEM;


typedef
BOOLEAN
(NTAPI *PFNKSFASTHANDLER)(
    IN PFILE_OBJECT FileObject,
    IN PKSIDENTIFIER Request,
    IN ULONG RequestLength,
    IN OUT PVOID Data,
    IN ULONG DataLength,
    OUT PIO_STATUS_BLOCK IoStatus
);

typedef struct {
    ULONG                       PropertyId;
    union {
        PFNKSFASTHANDLER            GetPropertyHandler;
        BOOLEAN                     GetSupported;
    };
    union {
        PFNKSFASTHANDLER            SetPropertyHandler;
        BOOLEAN                     SetSupported;
    };
    ULONG                       Reserved;
} KSFASTPROPERTY_ITEM, *PKSFASTPROPERTY_ITEM;

typedef struct {
    const GUID* Set;
    ULONG PropertiesCount;
    const KSPROPERTY_ITEM * PropertyItem;
    ULONG FastIoCount;
    const KSFASTPROPERTY_ITEM* FastIoTable;
} KSPROPERTY_SET, *PKSPROPERTY_SET;

#endif

typedef struct {
    ULONG                       SteppingDelta;
    ULONG                       Reserved;
    KSPROPERTY_BOUNDS_LONG      Bounds;
} KSPROPERTY_STEPPING_LONG, *PKSPROPERTY_STEPPING_LONG;

typedef struct {
#if defined(_NTDDK_)
    ULONGLONG                   SteppingDelta;
#else
    DWORDLONG                   SteppingDelta;
#endif
    KSPROPERTY_BOUNDS_LONGLONG  Bounds;
} KSPROPERTY_STEPPING_LONGLONG, *PKSPROPERTY_STEPPING_LONGLONG;

/* ===============================================================
    Allocator Framing
*/

typedef struct {
    union {
        ULONG       OptionsFlags;
        ULONG       RequirementsFlags;
    };
#if defined(_NTDDK_)
    POOL_TYPE   PoolType;
#else
    ULONG       PoolType;
#endif
    ULONG       Frames;
    ULONG       FrameSize;
    ULONG       FileAlignment;
    ULONG       Reserved;
} KSALLOCATOR_FRAMING, *PKSALLOCATOR_FRAMING;

typedef struct {
    ULONG               CountItems;
    ULONG               PinFlags;
    KS_COMPRESSION      OutputCompression;
    ULONG               PinWeight;
    KS_FRAMING_ITEM     FramingItem[1];
} KSALLOCATOR_FRAMING_EX, *PKSALLOCATOR_FRAMING_EX;

#define KSALLOCATOR_REQUIREMENTF_INPLACE_MODIFIER   0x00000001
#define KSALLOCATOR_REQUIREMENTF_SYSTEM_MEMORY      0x00000002
#define KSALLOCATOR_REQUIREMENTF_FRAME_INTEGRITY    0x00000004
#define KSALLOCATOR_REQUIREMENTF_MUST_ALLOCATE      0x00000008
#define KSALLOCATOR_REQUIREMENTF_PREFERENCES_ONLY   0x80000000

#define KSALLOCATOR_OPTIONF_COMPATIBLE              0x00000001
#define KSALLOCATOR_OPTIONF_SYSTEM_MEMORY           0x00000002
#define KSALLOCATOR_OPTIONF_VALID                   0x00000003

#define KSALLOCATOR_FLAG_PARTIAL_READ_SUPPORT       0x00000010
#define KSALLOCATOR_FLAG_DEVICE_SPECIFIC            0x00000020
#define KSALLOCATOR_FLAG_CAN_ALLOCATE               0x00000040
#define KSALLOCATOR_FLAG_INSIST_ON_FRAMESIZE_RATIO  0x00000080

/* ===============================================================
    Quality
*/

typedef struct {
    PVOID       Context;
    ULONG       Proportion;
    LONGLONG    DeltaTime;
} KSQUALITY, *PKSQUALITY;

typedef struct {
    HANDLE QualityManager;
    PVOID Context;
} KSQUALITY_MANAGER, *PKSQUALITY_MANAGER;

typedef struct {
    LONGLONG        PresentationStart;
    LONGLONG        Duration;
    KSPIN_INTERFACE Interface;
    LONG            Rate;
    ULONG           Flags;
} KSRATE, *PKSRATE;

typedef struct {
    KSPROPERTY      Property;
    KSRATE          Rate;
} KSRATE_CAPABILITY, *PKSRATE_CAPABILITY;

typedef struct {
    LONGLONG Granularity;
    LONGLONG Error;
} KSRESOLUTION, *PKSRESOLUTION;

typedef struct {
    ULONG       NotificationType;
    union {
        struct {
            HANDLE              Event;
            ULONG_PTR           Reserved[2];
        } EventHandle;
        struct {
            HANDLE              Semaphore;
            ULONG               Reserved;
            LONG                Adjustment;
        } SemaphoreHandle;
#if defined(_NTDDK_)
        struct {
            PVOID               Event;
            KPRIORITY           Increment;
            ULONG_PTR           Reserved;
        } EventObject;
        struct {
            PVOID               Semaphore;
            KPRIORITY           Increment;
            LONG                Adjustment;
        } SemaphoreObject;
        struct {
            PKDPC               Dpc;
            ULONG               ReferenceCount;
            ULONG_PTR           Reserved;
        } Dpc;
        struct {
            PWORK_QUEUE_ITEM    WorkQueueItem;
            WORK_QUEUE_TYPE     WorkQueueType;
            ULONG_PTR           Reserved;
        } WorkItem;
        struct {
            PWORK_QUEUE_ITEM    WorkQueueItem;
            PKSWORKER           KsWorkerObject;
            ULONG_PTR           Reserved;
        } KsWorkItem;
#endif
        struct {
            PVOID               Unused;
            LONG_PTR            Alignment[2];
        } Alignment;
    };
} KSEVENTDATA, *PKSEVENTDATA;

#define KSEVENTF_EVENT_HANDLE       0x00000001
#define KSEVENTF_SEMAPHORE_HANDLE   0x00000002
#if defined(_NTDDK_)
    #define KSEVENTF_EVENT_OBJECT       0x00000004
    #define KSEVENTF_SEMAPHORE_OBJECT   0x00000008
    #define KSEVENTF_DPC                0x00000010
    #define KSEVENTF_WORKITEM           0x00000020
    #define KSEVENTF_KSWORKITEM         0x00000080
#endif


#define KSEVENT_TYPE_ENABLE         0x00000001
#define KSEVENT_TYPE_ONESHOT        0x00000002
#define KSEVENT_TYPE_ENABLEBUFFERED 0x00000004
#define KSEVENT_TYPE_SETSUPPORT     0x00000100
#define KSEVENT_TYPE_BASICSUPPORT   0x00000200
#define KSEVENT_TYPE_QUERYBUFFER    0x00000400

#define KSEVENT_TYPE_TOPOLOGY 0x10000000

typedef struct {
    ULONG Size;
    ULONG Flags;
    union {
        HANDLE ObjectHandle;
        PVOID ObjectPointer;
    };
    PVOID Reserved;
    KSEVENT Event;
    KSEVENTDATA EventData;
} KSRELATIVEEVENT, *PKSRELATIVEEVENT;

#define KSRELATIVEEVENT_FLAG_HANDLE 0x00000001
#define KSRELATIVEEVENT_FLAG_POINTER 0x00000002

/* ===============================================================
    Timing
*/


typedef struct {
    KSEVENTDATA     EventData;
    LONGLONG        MarkTime;
} KSEVENT_TIME_MARK, *PKSEVENT_TIME_MARK;

typedef struct {
    KSEVENTDATA     EventData;
    LONGLONG        TimeBase;
    LONGLONG        Interval;
} KSEVENT_TIME_INTERVAL, *PKSEVENT_TIME_INTERVAL;

typedef struct {
    LONGLONG        TimeBase;
    LONGLONG        Interval;
} KSINTERVAL, *PKSINTERVAL;



typedef struct {
    LONGLONG Time;
    ULONG Numerator;
    ULONG Denominator;
} KSTIME, *PKSTIME;

typedef struct {
    LONGLONG    Time;
    LONGLONG    SystemTime;
} KSCORRELATED_TIME, *PKSCORRELATED_TIME;

typedef struct {
    LONGLONG    Duration;
    ULONG       FrameFlags;
    ULONG       Reserved;
} KSFRAMETIME, *PKSFRAMETIME;


/* ===============================================================
    Clocks
*/

typedef PVOID   PKSDEFAULTCLOCK;

typedef struct {
    ULONG       CreateFlags;
} KSCLOCK_CREATE, *PKSCLOCK_CREATE;

#if defined(_NTDDK_)

typedef
LONGLONG
(FASTCALL *PFNKSCLOCK_GETTIME)(
    IN PFILE_OBJECT FileObject
);
typedef
LONGLONG
(FASTCALL *PFNKSCLOCK_CORRELATEDTIME)(
    IN PFILE_OBJECT FileObject,
    OUT PLONGLONG SystemTime);

typedef struct {
    PFNKSCLOCK_GETTIME GetTime;
    PFNKSCLOCK_GETTIME GetPhysicalTime;
    PFNKSCLOCK_CORRELATEDTIME GetCorrelatedTime;
    PFNKSCLOCK_CORRELATEDTIME GetCorrelatedPhysicalTime;
} KSCLOCK_FUNCTIONTABLE, *PKSCLOCK_FUNCTIONTABLE;


#define DEFINE_KSPROPERTY_ITEM_CLOCK_TIME(Handler)\
    DEFINE_KSPROPERTY_ITEM(\
                           KSPROPERTY_CLOCK_TIME,\
                           (Handler),\
                           sizeof(KSPROPERTY),\
                           sizeof(LONGLONG),\
                           NULL, NULL, 0, NULL, NULL, 0)

#define DEFINE_KSPROPERTY_ITEM_CLOCK_PHYSICALTIME(Handler)\
    DEFINE_KSPROPERTY_ITEM(\
                           KSPROPERTY_CLOCK_PHYSICALTIME,\
                           (Handler),\
                           sizeof(KSPROPERTY),\
                           sizeof(LONGLONG),\
                           NULL, NULL, 0, NULL, NULL, 0)

#define DEFINE_KSPROPERTY_ITEM_CLOCK_CORRELATEDTIME(Handler)\
    DEFINE_KSPROPERTY_ITEM(\
                           KSPROPERTY_CLOCK_CORRELATEDTIME,\
                           (Handler),\
                           sizeof(KSPROPERTY),\
                           sizeof(KSCORRELATED_TIME),\
                           NULL, NULL, 0, NULL, NULL, 0)

#define DEFINE_KSPROPERTY_ITEM_CLOCK_CORRELATEDPHYSICALTIME(Handler)\
    DEFINE_KSPROPERTY_ITEM(\
                           KSPROPERTY_CLOCK_CORRELATEDPHYSICALTIME,\
                           (Handler),\
                           sizeof(KSPROPERTY),\
                           sizeof(KSCORRELATED_TIME),\
                           NULL, NULL, 0, NULL, NULL, 0)

#define DEFINE_KSPROPERTY_ITEM_CLOCK_RESOLUTION(Handler)\
    DEFINE_KSPROPERTY_ITEM(\
                           KSPROPERTY_CLOCK_RESOLUTION,\
                           (Handler),\
                           sizeof(KSPROPERTY),\
                           sizeof(KSRESOLUTION),\
                           NULL, NULL, 0, NULL, NULL, 0)

#define DEFINE_KSPROPERTY_ITEM_CLOCK_STATE(Handler)\
    DEFINE_KSPROPERTY_ITEM(\
                           KSPROPERTY_CLOCK_STATE,\
                           (Handler),\
                           sizeof(KSPROPERTY),\
                           sizeof(KSSTATE),\
                           NULL, NULL, 0, NULL, NULL, 0)

#define DEFINE_KSPROPERTY_ITEM_CLOCK_FUNCTIONTABLE(Handler)\
    DEFINE_KSPROPERTY_ITEM(\
                           KSPROPERTY_CLOCK_FUNCTIONTABLE,\
                           (Handler),\
                           sizeof(KSPROPERTY),\
                           sizeof(KSCLOCK_FUNCTIONTABLE),\
                           NULL, NULL, 0, NULL, NULL, 0)

#define DEFINE_KSPROPERTY_CLOCKSET(ClockSet,\
                                   PropTime, PropPhysicalTime,\
                                   PropCorrelatedTime, PropCorrelatedPhysicalTime,\
                                   PropResolution, PropState, PropFunctionTable)\
DEFINE_KSPROPERTY_TABLE(ClockSet) {\
    DEFINE_KSPROPERTY_ITEM_CLOCK_TIME(PropTime),\
    DEFINE_KSPROPERTY_ITEM_CLOCK_PHYSICALTIME(PropPhysicalTime),\
    DEFINE_KSPROPERTY_ITEM_CLOCK_CORRELATEDTIME(PropCorrelatedTime),\
    DEFINE_KSPROPERTY_ITEM_CLOCK_CORRELATEDPHYSICALTIME(PropCorrelatedPhysicalTime),\
    DEFINE_KSPROPERTY_ITEM_CLOCK_RESOLUTION(PropResolution),\
    DEFINE_KSPROPERTY_ITEM_CLOCK_STATE(PropState),\
    DEFINE_KSPROPERTY_ITEM_CLOCK_FUNCTIONTABLE(PropFunctionTable)\
}

/* ===============================================================
    Objects ??? SORT ME!
*/

#define KSCREATE_ITEM_SECURITYCHANGED       0x1
#define KSCREATE_ITEM_WILDCARD              0x2
#define KSCREATE_ITEM_NOPARAMETERS          0x4
#define KSCREATE_ITEM_FREEONSTOP            0x8

typedef struct {
    PDRIVER_DISPATCH       Create;
    PVOID                  Context;
    UNICODE_STRING         ObjectClass;
    PSECURITY_DESCRIPTOR   SecurityDescriptor;
    ULONG                  Flags;
} KSOBJECT_CREATE_ITEM, *PKSOBJECT_CREATE_ITEM;

typedef struct {
    ULONG                    CreateItemsCount;
    PKSOBJECT_CREATE_ITEM    CreateItemsList;
} KSOBJECT_CREATE, *PKSOBJECT_CREATE;

typedef VOID (NTAPI *PFNKSITEMFREECALLBACK)(
    IN  PKSOBJECT_CREATE_ITEM CreateItem);

#endif

typedef struct {
    ULONG    Size;
    ULONG    Count;
} KSMULTIPLE_ITEM, *PKSMULTIPLE_ITEM;

typedef struct {
    KSEVENT         Event;
    PKSEVENTDATA    EventData;
    PVOID           Reserved;
} KSQUERYBUFFER, *PKSQUERYBUFFER;

typedef struct {
    PVOID       Context;
    ULONG       Status;
} KSERROR, *PKSERROR;

/* ===============================================================
    Methods
*/
#if defined(_NTDDK_)

typedef struct {
    ULONG                   MethodId;
    union {
        PFNKSHANDLER            MethodHandler;
        BOOLEAN                 MethodSupported;
    };
    ULONG                   MinMethod;
    ULONG                   MinData;
    PFNKSHANDLER            SupportHandler;
    ULONG                   Flags;
} KSMETHOD_ITEM, *PKSMETHOD_ITEM;

#ifndef _MSC_VER

#define DEFINE_KSMETHOD_ITEM(MethodId, Flags,\
                             MethodHandler,\
                             MinMethod, MinData, SupportHandler)\
{\
    MethodId, {(PFNKSHANDLER)MethodHandler}, MinMethod, MinData,\
    SupportHandler, Flags\
}

#else

#define DEFINE_KSMETHOD_ITEM(MethodId, Flags,\
                             MethodHandler,\
                             MinMethod, MinData, SupportHandler)\
{\
    MethodId, (PFNKSHANDLER)MethodHandler, MinMethod, MinData,\
    SupportHandler, Flags\
}



#endif


typedef struct {
    ULONG                   MethodId;
    union {
        PFNKSFASTHANDLER        MethodHandler;
        BOOLEAN                 MethodSupported;
    };
} KSFASTMETHOD_ITEM, *PKSFASTMETHOD_ITEM;

#define DEFINE_KSFASTMETHOD_ITEM(MethodId, MethodHandler)\
    {\
        MethodId, (PFNKSFASTHANDLER)MethodHandler\
    }


typedef struct {
    const GUID*             Set;
    ULONG                   MethodsCount;
    const KSMETHOD_ITEM*    MethodItem;
    ULONG                   FastIoCount;
    const KSFASTMETHOD_ITEM*FastIoTable;
} KSMETHOD_SET, *PKSMETHOD_SET;


#define DEFINE_KSMETHOD_SET(Set,\
                            MethodsCount,\
                            MethodItem,\
                            FastIoCount,\
                            FastIoTable)\
{\
    Set,\
    MethodsCount,\
    MethodItem,\
    FastIoCount,\
    FastIoTable\
}

#endif
/* ===============================================================
    Nodes
*/

typedef struct {
    KSPROPERTY      Property;
    ULONG           NodeId;
    ULONG           Reserved;
} KSP_NODE, *PKSP_NODE;

typedef struct {
    KSMETHOD Method;
    ULONG NodeID;
    ULONG Reserved;
} KSM_NODE, *PKSM_NODE;

typedef struct {
    KSEVENT         Event;
    ULONG           NodeId;
    ULONG           Reserved;
} KSE_NODE, *PKSE_NODE;

typedef struct {
    ULONG       CreateFlags;
    ULONG       Node;
} KSNODE_CREATE, *PKSNODE_CREATE;


/* ===============================================================
    Events
*/
typedef struct _KSEVENT_ENTRY KSEVENT_ENTRY, *PKSEVENT_ENTRY;

#if defined(_NTDDK_)

typedef NTSTATUS(NTAPI *PFNKSADDEVENT)(
    IN  PIRP Irp,
    IN  PKSEVENTDATA EventData,
    IN  struct _KSEVENT_ENTRY* EventEntry);

typedef
VOID
(NTAPI *PFNKSREMOVEEVENT)(
    IN PFILE_OBJECT FileObject,
    IN struct _KSEVENT_ENTRY* EventEntry
);

typedef struct {
    ULONG               EventId;
    ULONG               DataInput;
    ULONG               ExtraEntryData;
    PFNKSADDEVENT       AddHandler;
    PFNKSREMOVEEVENT    RemoveHandler;
    PFNKSHANDLER        SupportHandler;
} KSEVENT_ITEM, *PKSEVENT_ITEM;

typedef struct {
    const GUID*         Set;
    ULONG               EventsCount;
    const KSEVENT_ITEM* EventItem;
} KSEVENT_SET, *PKSEVENT_SET;

struct _KSEVENT_ENTRY {
    LIST_ENTRY      ListEntry;
    PVOID           Object;
    union {
        PKSDPC_ITEM         DpcItem;
        PKSBUFFER_ITEM      BufferItem;
    };
    PKSEVENTDATA        EventData;
    ULONG               NotificationType;
    const KSEVENT_SET*  EventSet;
    const KSEVENT_ITEM* EventItem;
    PFILE_OBJECT        FileObject;
    ULONG               SemaphoreAdjustment;
    ULONG               Reserved;
    ULONG               Flags;
};

#endif
/* ===============================================================
    Pins
*/

#if defined(_NTDDK_)

typedef struct _KSPIN  KSPIN, *PKSPIN;
typedef struct _KSSTREAM_POINTER KSSTREAM_POINTER, *PKSSTREAM_POINTER;
typedef struct _KSSTREAM_POINTER_OFFSET KSSTREAM_POINTER_OFFSET, *PKSSTREAM_POINTER_OFFSET;
typedef struct _KSMAPPING KSMAPPING, *PKSMAPPING;
typedef struct _KSPROCESSPIN KSPROCESSPIN, *PKSPROCESSPIN;

#define IOCTL_KS_HANDSHAKE             CTL_CODE(FILE_DEVICE_KS, 0x007, METHOD_NEITHER, FILE_ANY_ACCESS)

typedef struct {
    GUID ProtocolId;
    PVOID Argument1;
    PVOID Argument2;
} KSHANDSHAKE, *PKSHANDSHAKE;

typedef
NTSTATUS
(NTAPI *PFNKSPINHANDSHAKE)(
    IN PKSPIN Pin,
    IN PKSHANDSHAKE In,
    IN PKSHANDSHAKE Out
);

typedef
void
(NTAPI *PFNKSPINPOWER)(
    IN PKSPIN Pin,
    IN DEVICE_POWER_STATE State
);

typedef
void
(NTAPI *PFNKSPINFRAMERETURN)(
    IN PKSPIN Pin,
    IN PVOID Data OPTIONAL,
    IN ULONG Size OPTIONAL,
    IN PMDL Mdl OPTIONAL,
    IN PVOID Context OPTIONAL,
    IN NTSTATUS Status
);

typedef
void
(NTAPI *PFNKSPINIRPCOMPLETION)(
    IN PKSPIN Pin,
    IN PIRP Irp
);

typedef
NTSTATUS
(NTAPI *PFNKSPINIRP)(
    IN PKSPIN Pin,
    IN PIRP Irp
);

typedef
NTSTATUS
(NTAPI *PFNKSPIN)(
    IN PKSPIN Pin
);

typedef
void
(NTAPI *PFNKSPINVOID)(
    IN PKSPIN Pin
);

typedef
void
(NTAPI *PFNKSSTREAMPOINTER)(
    IN PKSSTREAM_POINTER StreamPointer
);

typedef struct {
    ULONG Count;
    PKSATTRIBUTE* Attributes;
} KSATTRIBUTE_LIST, *PKSATTRIBUTE_LIST;

typedef
NTSTATUS
(NTAPI *PFNKSPINSETDATAFORMAT)(
    IN PKSPIN Pin,
    IN PKSDATAFORMAT OldFormat OPTIONAL,
    IN PKSMULTIPLE_ITEM OldAttributeList OPTIONAL,
    IN const KSDATARANGE* DataRange,
    IN const KSATTRIBUTE_LIST* AttributeRange OPTIONAL
);

typedef
NTSTATUS
(NTAPI *PFNKSPINSETDEVICESTATE)(
    IN PKSPIN Pin,
    IN KSSTATE ToState,
    IN KSSTATE FromState
);

typedef struct _KSCLOCK_DISPATCH KSCLOCK_DISPATCH, *PKSCLOCK_DISPATCH;
typedef struct _KSALLOCATOR_DISPATCH KSALLOCATOR_DISPATCH, *PKSALLOCATOR_DISPATCH;

typedef struct {
    PFNKSPINIRP Create;
    PFNKSPINIRP Close;
    PFNKSPIN Process;
    PFNKSPINVOID Reset;
    PFNKSPINSETDATAFORMAT SetDataFormat;
    PFNKSPINSETDEVICESTATE SetDeviceState;
    PFNKSPIN Connect;
    PFNKSPINVOID Disconnect;
    const KSCLOCK_DISPATCH* Clock;
    const KSALLOCATOR_DISPATCH* Allocator;
} KSPIN_DISPATCH, *PKSPIN_DISPATCH;

typedef
BOOLEAN
(NTAPI *PFNKSPINSETTIMER)(
    IN PKSPIN Pin,
    IN PKTIMER Timer,
    IN LARGE_INTEGER DueTime,
    IN PKDPC Dpc
);

typedef
BOOLEAN
(NTAPI *PFNKSPINCANCELTIMER)(
    IN PKSPIN Pin,
    IN PKTIMER Timer
);

typedef
LONGLONG
(FASTCALL *PFNKSPINCORRELATEDTIME)(
    IN PKSPIN Pin,
    OUT PLONGLONG SystemTime
);

typedef
void
(NTAPI *PFNKSPINRESOLUTION)(
    IN PKSPIN Pin,
    OUT PKSRESOLUTION Resolution
);

struct _KSCLOCK_DISPATCH {
    PFNKSPINSETTIMER SetTimer;
    PFNKSPINCANCELTIMER CancelTimer;
    PFNKSPINCORRELATEDTIME CorrelatedTime;
    PFNKSPINRESOLUTION Resolution;
};

typedef
NTSTATUS
(NTAPI *PFNKSPININITIALIZEALLOCATOR)(
    IN PKSPIN Pin,
    IN PKSALLOCATOR_FRAMING AllocatorFraming,
    OUT PVOID* Context
);

typedef PVOID(NTAPI *PFNKSDELETEALLOCATOR)(
    IN  PVOID Context);

typedef PVOID(NTAPI *PFNKSDEFAULTALLOCATE)(
    IN  PVOID Context);

typedef PVOID(NTAPI *PFNKSDEFAULTFREE)(
    IN  PVOID Context,
    IN  PVOID Buffer);

struct _KSALLOCATOR_DISPATCH {
    PFNKSPININITIALIZEALLOCATOR InitializeAllocator;
    PFNKSDELETEALLOCATOR DeleteAllocator;
    PFNKSDEFAULTALLOCATE Allocate;
    PFNKSDEFAULTFREE Free;
};

typedef struct {
    ULONG PropertySetsCount;
    ULONG PropertyItemSize;
    const KSPROPERTY_SET* PropertySets;
    ULONG MethodSetsCount;
    ULONG MethodItemSize;
    const KSMETHOD_SET* MethodSets;
    ULONG EventSetsCount;
    ULONG EventItemSize;
    const KSEVENT_SET* EventSets;
#if !defined(_WIN64)
    PVOID Alignment;
#endif
} KSAUTOMATION_TABLE, *PKSAUTOMATION_TABLE;



typedef struct {
    ULONG                   InterfacesCount;
    const KSPIN_INTERFACE*  Interfaces;
    ULONG                   MediumsCount;
    const KSPIN_MEDIUM*     Mediums;
    ULONG                   DataRangesCount;
    const PKSDATARANGE*     DataRanges;
    KSPIN_DATAFLOW          DataFlow;
    KSPIN_COMMUNICATION     Communication;
    const GUID*             Category;
    const GUID*             Name;
    union {
        LONGLONG            Reserved;
        struct {
            ULONG           ConstrainedDataRangesCount;
            PKSDATARANGE*   ConstrainedDataRanges;
        };
    };
} KSPIN_DESCRIPTOR, *PKSPIN_DESCRIPTOR;

typedef
NTSTATUS
(NTAPI *PFNKSINTERSECTHANDLER)(
    IN PIRP Irp,
    IN PKSP_PIN Pin,
    IN PKSDATARANGE DataRange,
    OUT PVOID Data OPTIONAL
);

typedef
NTSTATUS
(NTAPI *PFNKSINTERSECTHANDLEREX)(
    IN PVOID Context,
    IN PIRP Irp,
    IN PKSP_PIN Pin,
    IN PKSDATARANGE DataRange,
    IN PKSDATARANGE MatchingDataRange,
    IN ULONG DataBufferSize,
    OUT PVOID Data OPTIONAL,
    OUT PULONG DataSize
);

typedef struct {
    const KSPIN_DISPATCH* Dispatch;
    const KSAUTOMATION_TABLE* AutomationTable;
    KSPIN_DESCRIPTOR PinDescriptor;
    ULONG Flags;
    ULONG InstancesPossible;
    ULONG InstancesNecessary;
    const KSALLOCATOR_FRAMING_EX* AllocatorFraming;
    PFNKSINTERSECTHANDLEREX IntersectHandler;
} KSPIN_DESCRIPTOR_EX, *PKSPIN_DESCRIPTOR_EX;

#define KSFILTER_FLAG_DISPATCH_LEVEL_PROCESSING 0x00000001
#define KSFILTER_FLAG_CRITICAL_PROCESSING 0x00000002
#define KSFILTER_FLAG_HYPERCRITICAL_PROCESSING 0x00000004
#define KSFILTER_FLAG_RECEIVE_ZERO_LENGTH_SAMPLES 0x00000008
#if (NTDDI_VERSION >= NTDDI_WINXPSP2)
    #define KSFILTER_FLAG_DENY_USERMODE_ACCESS 0x80000000
#endif


#define KSPIN_FLAG_DISPATCH_LEVEL_PROCESSING KSFILTER_FLAG_DISPATCH_LEVEL_PROCESSING
#define KSPIN_FLAG_CRITICAL_PROCESSING KSFILTER_FLAG_CRITICAL_PROCESSING
#define KSPIN_FLAG_HYPERCRITICAL_PROCESSING KSFILTER_FLAG_HYPERCRITICAL_PROCESSING
#define KSPIN_FLAG_ASYNCHRONOUS_PROCESSING 0x00000008
#define KSPIN_FLAG_DO_NOT_INITIATE_PROCESSING 0x00000010
#define KSPIN_FLAG_INITIATE_PROCESSING_ON_EVERY_ARRIVAL 0x00000020
#define KSPIN_FLAG_FRAMES_NOT_REQUIRED_FOR_PROCESSING 0x00000040
#define KSPIN_FLAG_ENFORCE_FIFO 0x00000080

#define KSPIN_FLAG_GENERATE_MAPPINGS 0x00000100
#define KSPIN_FLAG_DISTINCT_TRAILING_EDGE 0x00000200

#define KSPIN_FLAG_PROCESS_IN_RUN_STATE_ONLY 0x00010000
#define KSPIN_FLAG_SPLITTER 0x00020000
#define KSPIN_FLAG_USE_STANDARD_TRANSPORT 0x00040000
#define KSPIN_FLAG_DO_NOT_USE_STANDARD_TRANSPORT 0x00080000
#define KSPIN_FLAG_FIXED_FORMAT 0x00100000
#define KSPIN_FLAG_GENERATE_EOS_EVENTS 0x00200000
#define KSPIN_FLAG_RENDERER (KSPIN_FLAG_PROCESS_IN_RUN_STATE_ONLY|KSPIN_FLAG_GENERATE_EOS_EVENTS)
#define KSPIN_FLAG_IMPLEMENT_CLOCK 0x00400000
#define KSPIN_FLAG_SOME_FRAMES_REQUIRED_FOR_PROCESSING 0x00800000
#define KSPIN_FLAG_PROCESS_IF_ANY_IN_RUN_STATE 0x01000000
#if (NTDDI_VERSION >= NTDDI_WINXPSP2)
    #define KSPIN_FLAG_DENY_USERMODE_ACCESS 0x80000000
#endif

struct _KSPIN {
    const KSPIN_DESCRIPTOR_EX* Descriptor;
    KSOBJECT_BAG Bag;
    PVOID Context;
    ULONG Id;
    KSPIN_COMMUNICATION Communication;
    BOOLEAN ConnectionIsExternal;
    KSPIN_INTERFACE ConnectionInterface;
    KSPIN_MEDIUM ConnectionMedium;
    KSPRIORITY ConnectionPriority;
    PKSDATAFORMAT ConnectionFormat;
    PKSMULTIPLE_ITEM AttributeList;
    ULONG StreamHeaderSize;
    KSPIN_DATAFLOW DataFlow;
    KSSTATE DeviceState;
    KSRESET ResetState;
    KSSTATE ClientState;
};

#define DEFINE_KSPROPERTY_ITEM_PIN_CINSTANCES(Handler)\
    DEFINE_KSPROPERTY_ITEM(\
                           KSPROPERTY_PIN_CINSTANCES,\
                           (Handler),\
                           sizeof(KSP_PIN),\
                           sizeof(KSPIN_CINSTANCES),\
                           NULL, NULL, 0, NULL, NULL, 0)

#define DEFINE_KSPROPERTY_ITEM_PIN_CTYPES(Handler)\
    DEFINE_KSPROPERTY_ITEM(\
                           KSPROPERTY_PIN_CTYPES,\
                           (Handler),\
                           sizeof(KSPROPERTY),\
                           sizeof(ULONG),\
                           NULL, NULL, 0, NULL, NULL, 0)

#define DEFINE_KSPROPERTY_ITEM_PIN_DATAFLOW(Handler)\
    DEFINE_KSPROPERTY_ITEM(\
                           KSPROPERTY_PIN_DATAFLOW,\
                           (Handler),\
                           sizeof(KSP_PIN),\
                           sizeof(KSPIN_DATAFLOW),\
                           NULL, NULL, 0, NULL, NULL, 0)

#define DEFINE_KSPROPERTY_ITEM_PIN_DATARANGES(Handler)\
    DEFINE_KSPROPERTY_ITEM(\
                           KSPROPERTY_PIN_DATARANGES,\
                           (Handler),\
                           sizeof(KSP_PIN),\
                           0,\
                           NULL, NULL, 0, NULL, NULL, 0)

#define DEFINE_KSPROPERTY_ITEM_PIN_DATAINTERSECTION(Handler)\
    DEFINE_KSPROPERTY_ITEM(\
                           KSPROPERTY_PIN_DATAINTERSECTION,\
                           (Handler),\
                           sizeof(KSP_PIN) + sizeof(KSMULTIPLE_ITEM),\
                           0,\
                           NULL, NULL, 0, NULL, NULL, 0)

#define DEFINE_KSPROPERTY_ITEM_PIN_INTERFACES(Handler)\
    DEFINE_KSPROPERTY_ITEM(\
                           KSPROPERTY_PIN_INTERFACES,\
                           (Handler),\
                           sizeof(KSP_PIN),\
                           0,\
                           NULL, NULL, 0, NULL, NULL, 0)

#define DEFINE_KSPROPERTY_ITEM_PIN_MEDIUMS(Handler)\
    DEFINE_KSPROPERTY_ITEM(\
                           KSPROPERTY_PIN_MEDIUMS,\
                           (Handler),\
                           sizeof(KSP_PIN),\
                           0,\
                           NULL, NULL, 0, NULL, NULL, 0)

#define DEFINE_KSPROPERTY_ITEM_PIN_COMMUNICATION(Handler)\
    DEFINE_KSPROPERTY_ITEM(\
                           KSPROPERTY_PIN_COMMUNICATION,\
                           (Handler),\
                           sizeof(KSP_PIN),\
                           sizeof(KSPIN_COMMUNICATION),\
                           NULL, NULL, 0, NULL, NULL, 0)

#define DEFINE_KSPROPERTY_ITEM_PIN_GLOBALCINSTANCES(Handler)\
    DEFINE_KSPROPERTY_ITEM(\
                           KSPROPERTY_PIN_GLOBALCINSTANCES,\
                           (Handler),\
                           sizeof(KSP_PIN),\
                           sizeof(KSPIN_CINSTANCES),\
                           NULL, NULL, 0, NULL, NULL, 0)

#define DEFINE_KSPROPERTY_ITEM_PIN_NECESSARYINSTANCES(Handler)\
    DEFINE_KSPROPERTY_ITEM(\
                           KSPROPERTY_PIN_NECESSARYINSTANCES,\
                           (Handler),\
                           sizeof(KSP_PIN),\
                           sizeof(ULONG),\
                           NULL, NULL, 0, NULL, NULL, 0)

#define DEFINE_KSPROPERTY_ITEM_PIN_PHYSICALCONNECTION(Handler)\
    DEFINE_KSPROPERTY_ITEM(\
                           KSPROPERTY_PIN_PHYSICALCONNECTION,\
                           (Handler),\
                           sizeof(KSP_PIN),\
                           0,\
                           NULL, NULL, 0, NULL, NULL, 0)

#define DEFINE_KSPROPERTY_ITEM_PIN_CATEGORY(Handler)\
    DEFINE_KSPROPERTY_ITEM(\
                           KSPROPERTY_PIN_CATEGORY,\
                           (Handler),\
                           sizeof(KSP_PIN),\
                           sizeof(GUID),\
                           NULL, NULL, 0, NULL, NULL, 0)

#define DEFINE_KSPROPERTY_ITEM_PIN_NAME(Handler)\
    DEFINE_KSPROPERTY_ITEM(\
                           KSPROPERTY_PIN_NAME,\
                           (Handler),\
                           sizeof(KSP_PIN),\
                           0,\
                           NULL, NULL, 0, NULL, NULL, 0)

#define DEFINE_KSPROPERTY_ITEM_PIN_CONSTRAINEDDATARANGES(Handler)\
    DEFINE_KSPROPERTY_ITEM(\
                           KSPROPERTY_PIN_CONSTRAINEDDATARANGES,\
                           (Handler),\
                           sizeof(KSP_PIN),\
                           0,\
                           NULL, NULL, 0, NULL, NULL, 0)

#define DEFINE_KSPROPERTY_ITEM_PIN_PROPOSEDATAFORMAT(Handler)\
    DEFINE_KSPROPERTY_ITEM(\
                           KSPROPERTY_PIN_PROPOSEDATAFORMAT,\
                           NULL,\
                           sizeof(KSP_PIN),\
                           sizeof(KSDATAFORMAT),\
                           (Handler), NULL, 0, NULL, NULL, 0)

#define DEFINE_KSPROPERTY_PINSET(PinSet,\
                                 PropGeneral, PropInstances, PropIntersection)\
DEFINE_KSPROPERTY_TABLE(PinSet) {\
    DEFINE_KSPROPERTY_ITEM_PIN_CINSTANCES(PropInstances),\
    DEFINE_KSPROPERTY_ITEM_PIN_CTYPES(PropGeneral),\
    DEFINE_KSPROPERTY_ITEM_PIN_DATAFLOW(PropGeneral),\
    DEFINE_KSPROPERTY_ITEM_PIN_DATARANGES(PropGeneral),\
    DEFINE_KSPROPERTY_ITEM_PIN_DATAINTERSECTION(PropIntersection),\
    DEFINE_KSPROPERTY_ITEM_PIN_INTERFACES(PropGeneral),\
    DEFINE_KSPROPERTY_ITEM_PIN_MEDIUMS(PropGeneral),\
    DEFINE_KSPROPERTY_ITEM_PIN_COMMUNICATION(PropGeneral),\
    DEFINE_KSPROPERTY_ITEM_PIN_CATEGORY(PropGeneral),\
    DEFINE_KSPROPERTY_ITEM_PIN_NAME(PropGeneral)\
}

#define DEFINE_KSPROPERTY_PINSETCONSTRAINED(PinSet,\
        PropGeneral, PropInstances, PropIntersection)\
DEFINE_KSPROPERTY_TABLE(PinSet) {\
    DEFINE_KSPROPERTY_ITEM_PIN_CINSTANCES(PropInstances),\
    DEFINE_KSPROPERTY_ITEM_PIN_CTYPES(PropGeneral),\
    DEFINE_KSPROPERTY_ITEM_PIN_DATAFLOW(PropGeneral),\
    DEFINE_KSPROPERTY_ITEM_PIN_DATARANGES(PropGeneral),\
    DEFINE_KSPROPERTY_ITEM_PIN_DATAINTERSECTION(PropIntersection),\
    DEFINE_KSPROPERTY_ITEM_PIN_INTERFACES(PropGeneral),\
    DEFINE_KSPROPERTY_ITEM_PIN_MEDIUMS(PropGeneral),\
    DEFINE_KSPROPERTY_ITEM_PIN_COMMUNICATION(PropGeneral),\
    DEFINE_KSPROPERTY_ITEM_PIN_CATEGORY(PropGeneral),\
    DEFINE_KSPROPERTY_ITEM_PIN_NAME(PropGeneral),\
    DEFINE_KSPROPERTY_ITEM_PIN_CONSTRAINEDDATARANGES(PropGeneral)\
}



typedef
void
(NTAPI *PFNKSFREE)(
    IN PVOID Data
);



#define DEFINE_KSPROPERTY_TABLE(tablename)\
    const KSPROPERTY_ITEM tablename[] =

#endif

typedef struct {
    KSPIN_INTERFACE Interface;
    KSPIN_MEDIUM Medium;
    ULONG PinId;
    HANDLE PinToHandle;
    KSPRIORITY Priority;
} KSPIN_CONNECT, *PKSPIN_CONNECT;

/* ===============================================================
    Topology
*/

typedef struct {
    ULONG FromNode;
    ULONG FromNodePin;
    ULONG ToNode;
    ULONG ToNodePin;
} KSTOPOLOGY_CONNECTION, *PKSTOPOLOGY_CONNECTION;

typedef struct {
    ULONG CategoriesCount;
    const GUID* Categories;
    ULONG TopologyNodesCount;
    const GUID* TopologyNodes;
    ULONG TopologyConnectionsCount;
    const KSTOPOLOGY_CONNECTION* TopologyConnections;
    const GUID* TopologyNodesNames;
    ULONG Reserved;
} KSTOPOLOGY, *PKSTOPOLOGY;


#define DEFINE_KSPROPERTY_ITEM_TOPOLOGY_CATEGORIES(Handler)\
    DEFINE_KSPROPERTY_ITEM(\
                           KSPROPERTY_TOPOLOGY_CATEGORIES,\
                           (Handler),\
                           sizeof(KSPROPERTY),\
                           0,\
                           NULL, NULL, 0, NULL, NULL, 0)

#define DEFINE_KSPROPERTY_ITEM_TOPOLOGY_NODES(Handler)\
    DEFINE_KSPROPERTY_ITEM(\
                           KSPROPERTY_TOPOLOGY_NODES,\
                           (Handler),\
                           sizeof(KSPROPERTY),\
                           0,\
                           NULL, NULL, 0, NULL, NULL, 0)

#define DEFINE_KSPROPERTY_ITEM_TOPOLOGY_CONNECTIONS(Handler)\
    DEFINE_KSPROPERTY_ITEM(\
                           KSPROPERTY_TOPOLOGY_CONNECTIONS,\
                           (Handler),\
                           sizeof(KSPROPERTY),\
                           0,\
                           NULL, NULL, 0, NULL, NULL, 0)

#define DEFINE_KSPROPERTY_ITEM_TOPOLOGY_NAME(Handler)\
    DEFINE_KSPROPERTY_ITEM(\
                           KSPROPERTY_TOPOLOGY_NAME,\
                           (Handler),\
                           sizeof(KSP_NODE),\
                           0,\
                           NULL, NULL, 0, NULL, NULL, 0)

#define DEFINE_KSPROPERTY_TOPOLOGYSET(TopologySet, Handler)\
    DEFINE_KSPROPERTY_TABLE(TopologySet) {\
        DEFINE_KSPROPERTY_ITEM_TOPOLOGY_CATEGORIES(Handler),\
        DEFINE_KSPROPERTY_ITEM_TOPOLOGY_NODES(Handler),\
        DEFINE_KSPROPERTY_ITEM_TOPOLOGY_CONNECTIONS(Handler),\
        DEFINE_KSPROPERTY_ITEM_TOPOLOGY_NAME(Handler)\
    }

/* ===============================================================
    ??? SORT ME
*/

/* TODO */
typedef void* UNKNOWN;

typedef PVOID(NTAPI *PFNKSINITIALIZEALLOCATOR)(
    IN  PVOID InitialContext,
    IN  PKSALLOCATOR_FRAMING AllocatorFraming,
    OUT PVOID* Context);

#if defined(_NTDDK_)
typedef NTSTATUS(NTAPI *PFNKSALLOCATOR)(
    IN  PIRP Irp,
    IN  ULONG BufferSize,
    IN  BOOLEAN InputOperation);

typedef NTSTATUS(NTAPI *PFNKINTERSECTHANDLEREX)(
    IN  PVOID Context,
    IN  PIRP Irp,
    IN  PKSP_PIN Pin,
    IN  PKSDATARANGE DataRange,
    IN  PKSDATARANGE MatchingDataRange,
    IN  ULONG DataBufferSize,
    OUT PVOID Data OPTIONAL,
    OUT PULONG DataSize);


typedef
NTSTATUS
(NTAPI *PFNALLOCATOR_ALLOCATEFRAME)(
    IN PFILE_OBJECT FileObject,
    PVOID *Frame
);

typedef
VOID
(NTAPI *PFNALLOCATOR_FREEFRAME)(
    IN PFILE_OBJECT FileObject,
    IN PVOID Frame
);

typedef struct {
    PFNALLOCATOR_ALLOCATEFRAME  AllocateFrame;
    PFNALLOCATOR_FREEFRAME      FreeFrame;
} KSSTREAMALLOCATOR_FUNCTIONTABLE, *PKSSTREAMALLOCATOR_FUNCTIONTABLE;

#endif

typedef struct {
    KSALLOCATOR_FRAMING Framing;
    ULONG AllocatedFrames;
    ULONG Reserved;
} KSSTREAMALLOCATOR_STATUS, *PKSSTREAMALLOCATOR_STATUS;

typedef struct {
    KSALLOCATOR_FRAMING_EX Framing;
    ULONG AllocatedFrames;
    ULONG Reserved;
} KSSTREAMALLOCATOR_STATUS_EX, *PKSSTREAMALLOCATOR_STATUS_EX;

typedef struct {
    ULONG Size;
    ULONG TypeSpecificFlags;
    KSTIME PresentationTime;
    LONGLONG Duration;
    ULONG FrameExtent;
    ULONG DataUsed;
    PVOID Data;
    ULONG OptionsFlags;
#ifdef _WIN64
    ULONG  Reserved;
#endif
} KSSTREAM_HEADER, *PKSSTREAM_HEADER;

#define KSSTREAM_HEADER_OPTIONSF_SPLICEPOINT        0x00000001
#define KSSTREAM_HEADER_OPTIONSF_PREROLL            0x00000002
#define KSSTREAM_HEADER_OPTIONSF_DATADISCONTINUITY  0x00000004
#define KSSTREAM_HEADER_OPTIONSF_TYPECHANGED        0x00000008
#define KSSTREAM_HEADER_OPTIONSF_TIMEVALID          0x00000010
#define KSSTREAM_HEADER_OPTIONSF_TIMEDISCONTINUITY  0x00000040
#define KSSTREAM_HEADER_OPTIONSF_FLUSHONPAUSE       0x00000080
#define KSSTREAM_HEADER_OPTIONSF_DURATIONVALID      0x00000100
#define KSSTREAM_HEADER_OPTIONSF_ENDOFSTREAM        0x00000200
#define KSSTREAM_HEADER_OPTIONSF_BUFFEREDTRANSFER   0x00000400
#define KSSTREAM_HEADER_OPTIONSF_VRAM_DATA_TRANSFER 0x00000800
#define KSSTREAM_HEADER_OPTIONSF_LOOPEDDATA         0x80000000

/* ===============================================================
    XP / DX8
*/
#if defined(_NTDDK_)

typedef struct _KSGATE KSGATE, *PKSGATE;

struct _KSGATE {
    LONG Count;
    PKSGATE NextGate;
};

#ifndef _NTOS_

static
void
__inline
KsGateTurnInputOn(
    IN PKSGATE Gate OPTIONAL)
{
    while (Gate && (InterlockedIncrement(&Gate->Count) == 1)) {
        Gate = Gate->NextGate;
    }
}

static
void
__inline
KsGateTurnInputOff(
    IN PKSGATE Gate OPTIONAL)
{
    while (Gate && (InterlockedDecrement(&Gate->Count) == 0)) {
        Gate = Gate->NextGate;
    }
}

static
BOOLEAN
__inline
KsGateGetStateUnsafe(
    IN PKSGATE Gate)
{
    ASSERT(Gate);
    return ((BOOLEAN)(Gate->Count > 0));
}

static
BOOLEAN
__inline
KsGateCaptureThreshold(
    IN PKSGATE Gate)
{
    BOOLEAN captured;
    ASSERT(Gate);
    captured = (BOOLEAN)(InterlockedCompareExchange(&Gate->Count, 0, 1) == 1);

    if (captured) {
        KsGateTurnInputOff(Gate->NextGate);
    }

    return captured;
}

static
void
__inline
KsGateInitialize(
    IN PKSGATE Gate,
    IN LONG InitialCount,
    IN PKSGATE NextGate OPTIONAL,
    IN BOOLEAN StateToPropagate
)
{
    ASSERT(Gate);
    Gate->Count = InitialCount;
    Gate->NextGate = NextGate;

    if (NextGate) {
        if (InitialCount > 0) {
            if (StateToPropagate) {
                KsGateTurnInputOn(NextGate);
            }
        } else {
            if (!StateToPropagate) {
                KsGateTurnInputOff(NextGate);
            }
        }
    }
}

static
void
__inline
KsGateInitializeAnd(
    IN PKSGATE AndGate,
    IN PKSGATE NextOrGate OPTIONAL)
{
    KsGateInitialize(AndGate, 1, NextOrGate, TRUE);
}

static
void
__inline
KsGateInitializeOr(
    IN PKSGATE OrGate,
    IN PKSGATE NextAndGate OPTIONAL)
{
    KsGateInitialize(OrGate, 0, NextAndGate, FALSE);
}

static
void
__inline
KsGateAddOnInputToAnd(
    IN PKSGATE AndGate)
{
    UNREFERENCED_PARAMETER(AndGate);
}

static
void
__inline
KsGateAddOffInputToAnd(
    IN PKSGATE AndGate)
{
    KsGateTurnInputOff(AndGate);
}

static
void
__inline
KsGateRemoveOnInputFromAnd(
    IN PKSGATE AndGate)
{
    UNREFERENCED_PARAMETER(AndGate);
}

static
void
__inline
KsGateRemoveOffInputFromAnd(
    IN PKSGATE AndGate)
{
    KsGateTurnInputOn(AndGate);
}

static
void
__inline
KsGateAddOnInputToOr(
    IN PKSGATE OrGate)
{
    KsGateTurnInputOn(OrGate);
}

static
void
__inline
KsGateAddOffInputToOr(
    IN PKSGATE OrGate)
{
    UNREFERENCED_PARAMETER(OrGate);
}

static
void
__inline
KsGateRemoveOnInputFromOr(
    IN PKSGATE OrGate)
{
    KsGateTurnInputOff(OrGate);
}

static
void
__inline
KsGateRemoveOffInputFromOr(
    IN PKSGATE OrGate)
{
    UNREFERENCED_PARAMETER(OrGate);
}

static
void
__inline
KsGateTerminateAnd(
    IN PKSGATE AndGate)
{
    ASSERT(AndGate);

    if (KsGateGetStateUnsafe(AndGate)) {
        KsGateRemoveOnInputFromOr(AndGate->NextGate);
    } else {
        KsGateRemoveOffInputFromOr(AndGate->NextGate);
    }
}

static
void
__inline
KsGateTerminateOr(
    IN PKSGATE OrGate)
{
    ASSERT(OrGate);

    if (KsGateGetStateUnsafe(OrGate)) {
        KsGateRemoveOnInputFromAnd(OrGate->NextGate);
    } else {
        KsGateRemoveOffInputFromAnd(OrGate->NextGate);
    }
}

#endif


struct _KSMAPPING {
    PHYSICAL_ADDRESS PhysicalAddress;
    ULONG ByteCount;
    ULONG Alignment;
};
#endif

typedef enum {
    KSSTREAM_POINTER_STATE_UNLOCKED = 0,
    KSSTREAM_POINTER_STATE_LOCKED
} KSSTREAM_POINTER_STATE;

typedef struct _KSPROCESSPIN_INDEXENTRY KSPROCESSPIN_INDEXENTRY, *PKSPROCESSPIN_INDEXENTRY;

struct _KSSTREAM_POINTER_OFFSET {
#if defined(_NTDDK_)
    union {
        PUCHAR Data;
        PKSMAPPING Mappings;
    };
#else
    PUCHAR Data;
#endif
#if !defined(_WIN64)
    PVOID Alignment;
#endif
    ULONG Count;
    ULONG Remaining;
};
#if defined(_NTDDK_)
struct _KSSTREAM_POINTER {
    PVOID Context;
    PKSPIN Pin;
    PKSSTREAM_HEADER StreamHeader;
    PKSSTREAM_POINTER_OFFSET Offset;
    KSSTREAM_POINTER_OFFSET OffsetIn;
    KSSTREAM_POINTER_OFFSET OffsetOut;
};

struct _KSPROCESSPIN {
    PKSPIN Pin;
    PKSSTREAM_POINTER StreamPointer;
    PKSPROCESSPIN InPlaceCounterpart;
    PKSPROCESSPIN DelegateBranch;
    PKSPROCESSPIN CopySource;
    PVOID Data;
    ULONG BytesAvailable;
    ULONG BytesUsed;
    ULONG Flags;
    BOOLEAN Terminate;
};

struct _KSPROCESSPIN_INDEXENTRY {
    PKSPROCESSPIN* Pins;
    ULONG Count;
};
#endif

/* ===============================================================
    Device Dispatch
*/



#if defined(_NTDDK_)

typedef struct _KSFILTER_DISPATCH KSFILTER_DISPATCH, *PKSFILTER_DISPATCH;
typedef struct _KSDEVICE KSDEVICE, *PKSDEVICE;
typedef struct _KSFILTER KSFILTER, *PKSFILTER;
typedef struct _KSNODE_DESCRIPTOR KSNODE_DESCRIPTOR, *PKSNODE_DESCRIPTOR;
typedef struct _KSFILTER_DESCRIPTOR KSFILTER_DESCRIPTOR, *PKSFILTER_DESCRIPTOR;
typedef struct _KSDEVICE_DESCRIPTOR KSDEVICE_DESCRIPTOR, *PKSDEVICE_DESCRIPTOR;

typedef NTSTATUS(NTAPI *PFNKSDEVICECREATE)(
    IN PKSDEVICE Device);

typedef NTSTATUS(NTAPI *PFNKSDEVICEPNPSTART)(
    IN PKSDEVICE Device,
    IN PIRP Irp,
    IN PCM_RESOURCE_LIST TranslatedResourceList OPTIONAL,
    IN PCM_RESOURCE_LIST UntranslatedResourceList OPTIONAL);

typedef NTSTATUS(NTAPI *PFNKSDEVICE)(
    IN PKSDEVICE Device);

typedef NTSTATUS(NTAPI *PFNKSDEVICEIRP)(
    IN PKSDEVICE Device,
    IN PIRP Irp);

typedef VOID (NTAPI *PFNKSDEVICEIRPVOID)(
    IN PKSDEVICE Device,
    IN PIRP Irp);

typedef NTSTATUS(NTAPI *PFNKSDEVICEQUERYCAPABILITIES)(
    IN PKSDEVICE Device,
    IN PIRP Irp,
    IN OUT PDEVICE_CAPABILITIES Capabilities);

typedef NTSTATUS(NTAPI *PFNKSDEVICEQUERYPOWER)(
    IN PKSDEVICE Device,
    IN PIRP Irp,
    IN DEVICE_POWER_STATE DeviceTo,
    IN DEVICE_POWER_STATE DeviceFrom,
    IN SYSTEM_POWER_STATE SystemTo,
    IN SYSTEM_POWER_STATE SystemFrom,
    IN POWER_ACTION Action);

typedef VOID (NTAPI *PFNKSDEVICESETPOWER)(
    IN PKSDEVICE Device,
    IN PIRP Irp,
    IN DEVICE_POWER_STATE To,
    IN DEVICE_POWER_STATE From);

typedef struct _KSDEVICE_DISPATCH {
    PFNKSDEVICECREATE Add;
    PFNKSDEVICEPNPSTART Start;
    PFNKSDEVICE PostStart;
    PFNKSDEVICEIRP QueryStop;
    PFNKSDEVICEIRPVOID CancelStop;
    PFNKSDEVICEIRPVOID Stop;
    PFNKSDEVICEIRP QueryRemove;
    PFNKSDEVICEIRPVOID CancelRemove;
    PFNKSDEVICEIRPVOID Remove;
    PFNKSDEVICEQUERYCAPABILITIES QueryCapabilities;
    PFNKSDEVICEIRPVOID SurpriseRemoval;
    PFNKSDEVICEQUERYPOWER QueryPower;
    PFNKSDEVICESETPOWER SetPower;
    PFNKSDEVICEIRP QueryInterface;
} KSDEVICE_DISPATCH, *PKSDEVICE_DISPATCH;

#if (NTDDI_VERSION >= NTDDI_LONGHORN)
    #define KSDEVICE_DESCRIPTOR_VERSION_2 (0x110)
    #define MIN_DEV_VER_FOR_FLAGS (0x110)
#endif

struct _KSDEVICE {
    const KSDEVICE_DESCRIPTOR* Descriptor;
    KSOBJECT_BAG Bag;
    PVOID Context;
    PDEVICE_OBJECT FunctionalDeviceObject;
    PDEVICE_OBJECT PhysicalDeviceObject;
    PDEVICE_OBJECT NextDeviceObject;
    BOOLEAN Started;
    SYSTEM_POWER_STATE SystemPowerState;
    DEVICE_POWER_STATE DevicePowerState;
};
#endif

/* ===============================================================
    Filter Dispatch
*/
#if defined(_NTDDK_)
struct _KSFILTER {
    const KSFILTER_DESCRIPTOR* Descriptor;
    KSOBJECT_BAG Bag;
    PVOID Context;
};

typedef
void
(NTAPI *PFNKSFILTERPOWER)(
    IN PKSFILTER Filter,
    IN DEVICE_POWER_STATE State
);

typedef NTSTATUS(NTAPI *PFNKSFILTERIRP)(
    IN PKSFILTER Filter,
    IN PIRP Irp);

typedef NTSTATUS(NTAPI *PFNKSFILTERPROCESS)(
    IN PKSFILTER Filter,
    IN PKSPROCESSPIN_INDEXENTRY ProcessPinsIndex);

typedef NTSTATUS(NTAPI *PFNKSFILTERVOID)(
    IN PKSFILTER Filter);

struct _KSFILTER_DISPATCH {
    PFNKSFILTERIRP Create;
    PFNKSFILTERIRP Close;
    PFNKSFILTERPROCESS Process;
    PFNKSFILTERVOID Reset;
};

struct _KSNODE_DESCRIPTOR {
    const KSAUTOMATION_TABLE*  AutomationTable;
    const GUID*  Type;
    const GUID*  Name;
#if !defined(_WIN64)
    PVOID Alignment;
#endif
};

struct _KSFILTER_DESCRIPTOR {
    const KSFILTER_DISPATCH*  Dispatch;
    const KSAUTOMATION_TABLE*  AutomationTable;
    ULONG  Version;
    ULONG  Flags;
    const GUID*  ReferenceGuid;
    ULONG  PinDescriptorsCount;
    ULONG  PinDescriptorSize;
    const KSPIN_DESCRIPTOR_EX*  PinDescriptors;
    ULONG  CategoriesCount;
    const GUID*  Categories;
    ULONG  NodeDescriptorsCount;
    ULONG  NodeDescriptorSize;
    const KSNODE_DESCRIPTOR*  NodeDescriptors;
    ULONG  ConnectionsCount;
    const KSTOPOLOGY_CONNECTION*  Connections;
    const KSCOMPONENTID*  ComponentId;
};

#define KSFILTER_DESCRIPTOR_VERSION ((ULONG)-1)

struct _KSDEVICE_DESCRIPTOR {
    const KSDEVICE_DISPATCH*  Dispatch;
    ULONG  FilterDescriptorsCount;
    const  KSFILTER_DESCRIPTOR*const* FilterDescriptors;
    ULONG  Version;
    ULONG  Flags;
};

struct _KSFILTERFACTORY {
    const KSFILTER_DESCRIPTOR* FilterDescriptor;
    KSOBJECT_BAG Bag;
    PVOID Context;
};

#define DEFINE_KSFILTER_DESCRIPTOR(descriptor)\
    const KSFILTER_DESCRIPTOR descriptor =

#define DEFINE_KSFILTER_PIN_DESCRIPTORS(table)\
    SIZEOF_ARRAY(table),\
    sizeof(table[0]),\
    table

#define DEFINE_KSFILTER_CATEGORIES(table)\
    SIZEOF_ARRAY(table),\
    table

#define DEFINE_KSFILTER_CATEGORY(category)\
    1,\
    &(category)

#define DEFINE_KSFILTER_CATEGORIES_NULL\
    0,\
    NULL

#define DEFINE_KSFILTER_NODE_DESCRIPTORS(table)\
    SIZEOF_ARRAY(table),\
    sizeof(table[0]),\
    table

#define DEFINE_KSFILTER_NODE_DESCRIPTORS_NULL\
    0,\
    sizeof(KSNODE_DESCRIPTOR),\
    NULL

#define DEFINE_KSFILTER_CONNECTIONS(table)\
    SIZEOF_ARRAY(table),\
    table

#define DEFINE_KSFILTER_DEFAULT_CONNECTIONS\
    0,\
    NULL

#endif
/* ===============================================================
    Minidriver Callbacks
*/
#if defined(_NTDDK_)
typedef NTSTATUS(NTAPI *KStrMethodHandler)(
    IN  PIRP Irp,
    IN  PKSIDENTIFIER Request,
    IN  OUT PVOID Data);

typedef NTSTATUS(NTAPI *KStrSupportHandler)(
    IN  PIRP Irp,
    IN  PKSIDENTIFIER Request,
    IN  OUT PVOID Data);
#endif

/* ===============================================================
    Allocator Functions
*/
#if defined(_NTDDK_)
KSDDKAPI NTSTATUS NTAPI
KsCreateAllocator(
    IN  HANDLE ConnectionHandle,
    IN  PKSALLOCATOR_FRAMING AllocatorFraming,
    OUT PHANDLE AllocatorHandle);

KSDDKAPI NTSTATUS NTAPI
KsCreateDefaultAllocator(
    IN  PIRP Irp);

KSDDKAPI NTSTATUS NTAPI
KsValidateAllocatorCreateRequest(
    IN  PIRP Irp,
    OUT PKSALLOCATOR_FRAMING* AllocatorFraming);

KSDDKAPI NTSTATUS NTAPI
KsCreateDefaultAllocatorEx(
    IN  PIRP Irp,
    IN  PVOID InitializeContext OPTIONAL,
    IN  PFNKSDEFAULTALLOCATE DefaultAllocate OPTIONAL,
    IN  PFNKSDEFAULTFREE DefaultFree OPTIONAL,
    IN  PFNKSINITIALIZEALLOCATOR InitializeAllocator OPTIONAL,
    IN  PFNKSDELETEALLOCATOR DeleteAllocator OPTIONAL);

KSDDKAPI NTSTATUS NTAPI
KsValidateAllocatorFramingEx(
    IN  PKSALLOCATOR_FRAMING_EX Framing,
    IN  ULONG BufferSize,
    IN  const KSALLOCATOR_FRAMING_EX* PinFraming);
#endif

/* ===============================================================
    Clock Functions
*/
#if defined(_NTDDK_)
typedef BOOLEAN(NTAPI *PFNKSSETTIMER)(
    IN  PVOID Context,
    IN  PKTIMER Timer,
    IN  LARGE_INTEGER DueTime,
    IN  PKDPC Dpc);

typedef BOOLEAN(NTAPI *PFNKSCANCELTIMER)(
    IN  PVOID Context,
    IN  PKTIMER Timer);

typedef LONGLONG(FASTCALL *PFNKSCORRELATEDTIME)(
    IN  PVOID Context,
    OUT PLONGLONG SystemTime);

KSDDKAPI NTSTATUS NTAPI
KsCreateClock(
    IN  HANDLE ConnectionHandle,
    IN  PKSCLOCK_CREATE ClockCreate,
    OUT PHANDLE ClockHandle);

KSDDKAPI NTSTATUS NTAPI
KsCreateDefaultClock(
    IN  PIRP Irp,
    IN  PKSDEFAULTCLOCK DefaultClock);

KSDDKAPI NTSTATUS NTAPI
KsAllocateDefaultClock(
    OUT PKSDEFAULTCLOCK* DefaultClock);

KSDDKAPI NTSTATUS NTAPI
KsAllocateDefaultClockEx(
    OUT PKSDEFAULTCLOCK* DefaultClock,
    IN  PVOID Context OPTIONAL,
    IN  PFNKSSETTIMER SetTimer OPTIONAL,
    IN  PFNKSCANCELTIMER CancelTimer OPTIONAL,
    IN  PFNKSCORRELATEDTIME CorrelatedTime OPTIONAL,
    IN  const KSRESOLUTION* Resolution OPTIONAL,
    IN  ULONG Flags);

KSDDKAPI VOID NTAPI
KsFreeDefaultClock(
    IN  PKSDEFAULTCLOCK DefaultClock);

KSDDKAPI NTSTATUS NTAPI
KsValidateClockCreateRequest(
    IN  PIRP Irp,
    OUT PKSCLOCK_CREATE* ClockCreate);

KSDDKAPI KSSTATE NTAPI
KsGetDefaultClockState(
    IN  PKSDEFAULTCLOCK DefaultClock);

KSDDKAPI VOID NTAPI
KsSetDefaultClockState(
    IN  PKSDEFAULTCLOCK DefaultClock,
    IN  KSSTATE State);

KSDDKAPI LONGLONG NTAPI
KsGetDefaultClockTime(
    IN  PKSDEFAULTCLOCK DefaultClock);

KSDDKAPI VOID NTAPI
KsSetDefaultClockTime(
    IN  PKSDEFAULTCLOCK DefaultClock,
    IN  LONGLONG Time);
#endif

/* ===============================================================
    Method Functions
*/

/* Method sets - TODO: Make into macros! */
#if defined(_NTDDK_)
#if 0
VOID
KSMETHOD_SET_IRP_STORAGE(
    IN  IRP Irp);

VOID
KSMETHOD_ITEM_IRP_STORAGE(
    IN  IRP Irp);

VOID
KSMETHOD_TYPE_IRP_STORAGE(
    IN  IRP Irp);
#endif

KSDDKAPI NTSTATUS NTAPI
KsMethodHandler(
    IN  PIRP Irp,
    IN  ULONG MethodSetsCount,
    IN  PKSMETHOD_SET MethodSet);

KSDDKAPI NTSTATUS NTAPI
KsMethodHandlerWithAllocator(
    IN  PIRP Irp,
    IN  ULONG MethodSetsCount,
    IN  PKSMETHOD_SET MethodSet,
    IN  PFNKSALLOCATOR Allocator OPTIONAL,
    IN  ULONG MethodItemSize OPTIONAL);

KSDDKAPI BOOLEAN NTAPI
KsFastMethodHandler(
    IN  PFILE_OBJECT FileObject,
    IN  PKSMETHOD UNALIGNED Method,
    IN  ULONG MethodLength,
    IN  OUT PVOID UNALIGNED Data,
    IN  ULONG DataLength,
    OUT PIO_STATUS_BLOCK IoStatus,
    IN  ULONG MethodSetsCount,
    IN  const KSMETHOD_SET* MethodSet);
#endif

/* ===============================================================
    Property Functions
*/
#if defined(_NTDDK_)
KSDDKAPI NTSTATUS NTAPI
KsPropertyHandler(
    IN  PIRP Irp,
    IN  ULONG PropertySetsCount,
    IN  const KSPROPERTY_SET* PropertySet);

KSDDKAPI NTSTATUS NTAPI
KsPropertyHandlerWithAllocator(
    IN  PIRP Irp,
    IN  ULONG PropertySetsCount,
    IN  PKSPROPERTY_SET PropertySet,
    IN  PFNKSALLOCATOR Allocator OPTIONAL,
    IN  ULONG PropertyItemSize OPTIONAL);

KSDDKAPI NTSTATUS NTAPI
KsUnserializeObjectPropertiesFromRegistry(
    IN  PFILE_OBJECT FileObject,
    IN  HANDLE ParentKey OPTIONAL,
    IN  PUNICODE_STRING RegistryPath OPTIONAL);

KSDDKAPI BOOLEAN NTAPI
KsFastPropertyHandler(
    IN  PFILE_OBJECT FileObject,
    IN  PKSPROPERTY UNALIGNED Property,
    IN  ULONG PropertyLength,
    IN  OUT PVOID UNALIGNED Data,
    IN  ULONG DataLength,
    OUT PIO_STATUS_BLOCK IoStatus,
    IN  ULONG PropertySetsCount,
    IN  const KSPROPERTY_SET* PropertySet);
#endif

/* ===============================================================
    Event Functions
*/

#if defined(_NTDDK_)

#define KSPROBE_STREAMREAD      0x00000000
#define KSPROBE_STREAMWRITE     0x00000001
#define KSPROBE_ALLOCATEMDL     0x00000010
#define KSPROBE_PROBEANDLOCK    0x00000020
#define KSPROBE_SYSTEMADDRESS   0x00000040
#define KSPROBE_MODIFY          0x00000200
#define KSPROBE_STREAMWRITEMODIFY (KSPROBE_MODIFY | KSPROBE_STREAMWRITE)
#define KSPROBE_ALLOWFORMATCHANGE   0x00000080

#define KSSTREAM_READ           KSPROBE_STREAMREAD
#define KSSTREAM_WRITE          KSPROBE_STREAMWRITE
#define KSSTREAM_PAGED_DATA     0x00000000
#define KSSTREAM_NONPAGED_DATA  0x00000100
#define KSSTREAM_SYNCHRONOUS    0x00001000
#define KSSTREAM_FAILUREEXCEPTION 0x00002000

typedef
BOOLEAN
(NTAPI *PFNKSGENERATEEVENTCALLBACK)(
    IN PVOID Context,
    IN PKSEVENT_ENTRY EventEntry
);

KSDDKAPI NTSTATUS NTAPI
KsGenerateEvent(
    IN  PKSEVENT_ENTRY EntryEvent);

KSDDKAPI void NTAPI
KsGenerateEvents(
    IN PVOID Object,
    IN const GUID* EventSet OPTIONAL,
    IN ULONG EventId,
    IN ULONG DataSize,
    IN PVOID Data OPTIONAL,
    IN PFNKSGENERATEEVENTCALLBACK CallBack OPTIONAL,
    IN PVOID CallBackContext OPTIONAL
);


KSDDKAPI NTSTATUS NTAPI
KsEnableEventWithAllocator(
    IN  PIRP Irp,
    IN  ULONG EventSetsCount,
    IN  PKSEVENT_SET EventSet,
    IN  OUT PLIST_ENTRY EventsList OPTIONAL,
    IN  KSEVENTS_LOCKTYPE EventsFlags OPTIONAL,
    IN  PVOID EventsLock OPTIONAL,
    IN  PFNKSALLOCATOR Allocator OPTIONAL,
    IN  ULONG EventItemSize OPTIONAL);

KSDDKAPI NTSTATUS NTAPI
KsGenerateDataEvent(
    IN  PKSEVENT_ENTRY EventEntry,
    IN  ULONG DataSize,
    IN  PVOID Data);

KSDDKAPI NTSTATUS NTAPI
KsEnableEvent(
    IN  PIRP Irp,
    IN  ULONG EventSetsCount,
    IN  KSEVENT_SET* EventSet,
    IN  OUT PLIST_ENTRY EventsList OPTIONAL,
    IN  KSEVENTS_LOCKTYPE EventsFlags OPTIONAL,
    IN  PVOID EventsLock OPTIONAL);

KSDDKAPI VOID NTAPI
KsDiscardEvent(
    IN  PKSEVENT_ENTRY EventEntry);

KSDDKAPI NTSTATUS NTAPI
KsDisableEvent(
    IN  PIRP Irp,
    IN  OUT PLIST_ENTRY EventsList,
    IN  KSEVENTS_LOCKTYPE EventsFlags,
    IN  PVOID EventsLock);

KSDDKAPI VOID NTAPI
KsFreeEventList(
    IN  PFILE_OBJECT FileObject,
    IN  OUT PLIST_ENTRY EventsList,
    IN  KSEVENTS_LOCKTYPE EVentsFlags,
    IN  PVOID EventsLock);

/* ===============================================================
    Topology Functions
*/

KSDDKAPI NTSTATUS NTAPI
KsValidateTopologyNodeCreateRequest(
    IN  PIRP Irp,
    IN  PKSTOPOLOGY Topology,
    OUT PKSNODE_CREATE* NodeCreate);

KSDDKAPI NTSTATUS NTAPI
KsCreateTopologyNode(
    IN  HANDLE ParentHandle,
    IN  PKSNODE_CREATE NodeCreate,
    IN  ACCESS_MASK DesiredAccess,
    OUT PHANDLE NodeHandle);

KSDDKAPI NTSTATUS NTAPI
KsTopologyPropertyHandler(
    IN  PIRP Irp,
    IN  PKSPROPERTY Property,
    IN  OUT PVOID Data,
    IN  const KSTOPOLOGY* Topology);



/* ===============================================================
    Connectivity Functions
*/

KSDDKAPI NTSTATUS NTAPI
KsCreatePin(
    IN  HANDLE FilterHandle,
    IN  PKSPIN_CONNECT Connect,
    IN  ACCESS_MASK DesiredAccess,
    OUT PHANDLE ConnectionHandle);

KSDDKAPI NTSTATUS NTAPI
KsValidateConnectRequest(
    IN  PIRP Irp,
    IN  ULONG DescriptorsCount,
    IN  KSPIN_DESCRIPTOR* Descriptor,
    OUT PKSPIN_CONNECT* Connect);

KSDDKAPI NTSTATUS NTAPI
KsPinPropertyHandler(
    IN  PIRP Irp,
    IN  PKSPROPERTY Property,
    IN  OUT PVOID Data,
    IN  ULONG DescriptorsCount,
    IN  const KSPIN_DESCRIPTOR* Descriptor);

KSDDKAPI NTSTATUS NTAPI
KsPinDataIntersection(
    IN  PIRP Irp,
    IN  PKSP_PIN Pin,
    OUT PVOID Data,
    IN  ULONG DescriptorsCount,
    IN  const KSPIN_DESCRIPTOR* Descriptor,
    IN  PFNKSINTERSECTHANDLER IntersectHandler);

KSDDKAPI NTSTATUS NTAPI
KsPinDataIntersectionEx(
    IN  PIRP Irp,
    IN  PKSP_PIN Pin,
    OUT PVOID Data,
    IN  ULONG DescriptorsCount,
    IN  const KSPIN_DESCRIPTOR* Descriptor,
    IN  ULONG DescriptorSize,
    IN  PFNKSINTERSECTHANDLEREX IntersectHandler OPTIONAL,
    IN  PVOID HandlerContext OPTIONAL);

KSDDKAPI PKSFILTER NTAPI
KsPinGetParentFilter(
    IN PKSPIN Pin
);

KSDDKAPI PKSPIN NTAPI
KsPinGetNextSiblingPin(
    IN PKSPIN Pin
);


/* Does this belong here? */

KSDDKAPI NTSTATUS NTAPI
KsHandleSizedListQuery(
    IN  PIRP Irp,
    IN  ULONG DataItemsCount,
    IN  ULONG DataItemSize,
    IN  const VOID* DataItems);


/* ===============================================================
    IRP Helper Functions
*/

typedef NTSTATUS(NTAPI *PFNKSIRPLISTCALLBACK)(
    IN  PIRP Irp,
    IN  PVOID Context);

KSDDKAPI NTSTATUS NTAPI
KsAcquireResetValue(
    IN  PIRP Irp,
    OUT KSRESET* ResetValue);

KSDDKAPI VOID NTAPI
KsAddIrpToCancelableQueue(
    IN  OUT PLIST_ENTRY QueueHead,
    IN  PKSPIN_LOCK SpinLock,
    IN  PIRP Irp,
    IN  KSLIST_ENTRY_LOCATION ListLocation,
    IN  PDRIVER_CANCEL DriverCancel OPTIONAL);

KSDDKAPI NTSTATUS NTAPI
KsAddObjectCreateItemToDeviceHeader(
    IN  KSDEVICE_HEADER Header,
    IN  PDRIVER_DISPATCH Create,
    IN  PVOID Context,
    IN  PWCHAR ObjectClass,
    IN  PSECURITY_DESCRIPTOR SecurityDescriptor);

KSDDKAPI NTSTATUS NTAPI
KsAddObjectCreateItemToObjectHeader(
    IN  KSOBJECT_HEADER Header,
    IN  PDRIVER_DISPATCH Create,
    IN  PVOID Context,
    IN  PWCHAR ObjectClass,
    IN  PSECURITY_DESCRIPTOR SecurityDescriptor);

KSDDKAPI NTSTATUS NTAPI
KsAllocateDeviceHeader(
    OUT KSDEVICE_HEADER* Header,
    IN  ULONG ItemsCount,
    IN  PKSOBJECT_CREATE_ITEM ItemsList OPTIONAL);

KSDDKAPI NTSTATUS NTAPI
KsAllocateExtraData(
    IN  PIRP Irp,
    IN  ULONG ExtraSize,
    OUT PVOID* ExtraBuffer);

KSDDKAPI NTSTATUS NTAPI
KsAllocateObjectCreateItem(
    IN  KSDEVICE_HEADER Header,
    IN  PKSOBJECT_CREATE_ITEM CreateItem,
    IN  BOOLEAN AllocateEntry,
    IN  PFNKSITEMFREECALLBACK ItemFreeCallback OPTIONAL);

KSDDKAPI NTSTATUS NTAPI
KsAllocateObjectHeader(
    OUT KSOBJECT_HEADER *Header,
    IN  ULONG ItemsCount,
    IN  PKSOBJECT_CREATE_ITEM ItemsList OPTIONAL,
    IN  PIRP Irp,
    IN  KSDISPATCH_TABLE* Table);

KSDDKAPI VOID NTAPI
KsCancelIo(
    IN  OUT PLIST_ENTRY QueueHead,
    IN  PKSPIN_LOCK SpinLock);

KSDDKAPI VOID NTAPI
KsCancelRoutine(
    IN  PDEVICE_OBJECT DeviceObject,
    IN  PIRP Irp);

KSDDKAPI NTSTATUS NTAPI
KsDefaultDeviceIoCompletion(
    IN  PDEVICE_OBJECT DeviceObject,
    IN  PIRP Irp);

/* ELSEWHERE
KSDDKAPI ULONG NTAPI
KsDecrementCountedWorker(
    IN  PKSWORKER Worker);
*/

KSDDKAPI BOOLEAN NTAPI
KsDispatchFastIoDeviceControlFailure(
    IN  PFILE_OBJECT FileObject,
    IN  BOOLEAN Wait,
    IN  PVOID InputBuffer  OPTIONAL,
    IN  ULONG InputBufferLength,
    OUT PVOID OutputBuffer  OPTIONAL,
    IN  ULONG OutputBufferLength,
    IN  ULONG IoControlCode,
    OUT PIO_STATUS_BLOCK IoStatus,
    IN  PDEVICE_OBJECT DeviceObject);   /* always return false */

KSDDKAPI BOOLEAN NTAPI
KsDispatchFastReadFailure(
    IN  PFILE_OBJECT FileObject,
    IN  PLARGE_INTEGER FileOffset,
    IN  ULONG Length,
    IN  BOOLEAN Wait,
    IN  ULONG LockKey,
    OUT PVOID Buffer,
    OUT PIO_STATUS_BLOCK IoStatus,
    IN  PDEVICE_OBJECT DeviceObject);   /* always return false */

/* This function does the same as the above */
#define KsDispatchFastWriteFailure KsDispatchFastReadFailure

KSDDKAPI NTSTATUS NTAPI
KsDispatchInvalidDeviceRequest(
    IN  PDEVICE_OBJECT DeviceObject,
    IN  PIRP Irp);

KSDDKAPI NTSTATUS NTAPI
KsDispatchIrp(
    IN  PDEVICE_OBJECT DeviceObject,
    IN  PIRP Irp);

KSDDKAPI NTSTATUS NTAPI
KsDispatchSpecificMethod(
    IN  PIRP Irp,
    IN  PFNKSHANDLER Handler);

KSDDKAPI NTSTATUS NTAPI
KsDispatchSpecificProperty(
    IN  PIRP Irp,
    IN  PFNKSHANDLER Handler);

KSDDKAPI NTSTATUS NTAPI
KsForwardAndCatchIrp(
    IN  PDEVICE_OBJECT DeviceObject,
    IN  PIRP Irp,
    IN  PFILE_OBJECT FileObject,
    IN  KSSTACK_USE StackUse);

KSDDKAPI NTSTATUS NTAPI
KsForwardIrp(
    IN  PIRP Irp,
    IN  PFILE_OBJECT FileObject,
    IN  BOOLEAN ReuseStackLocation);

KSDDKAPI VOID NTAPI
KsFreeDeviceHeader(
    IN  KSDEVICE_HEADER Header);

KSDDKAPI VOID NTAPI
KsFreeObjectHeader(
    IN  PVOID Header);

KSDDKAPI NTSTATUS NTAPI
KsGetChildCreateParameter(
    IN  PIRP Irp,
    OUT PVOID* CreateParameter);

KSDDKAPI NTSTATUS NTAPI
KsMoveIrpsOnCancelableQueue(
    IN  OUT PLIST_ENTRY SourceList,
    IN  PKSPIN_LOCK SourceLock,
    IN  OUT PLIST_ENTRY DestinationList,
    IN  PKSPIN_LOCK DestinationLock OPTIONAL,
    IN  KSLIST_ENTRY_LOCATION ListLocation,
    IN  PFNKSIRPLISTCALLBACK ListCallback,
    IN  PVOID Context);

KSDDKAPI NTSTATUS NTAPI
KsProbeStreamIrp(
    IN  PIRP Irp,
    IN  ULONG ProbeFlags,
    IN  ULONG HeaderSize);

KSDDKAPI NTSTATUS NTAPI
KsQueryInformationFile(
    IN  PFILE_OBJECT FileObject,
    OUT PVOID FileInformation,
    IN  ULONG Length,
    IN  FILE_INFORMATION_CLASS FileInformationClass);

KSDDKAPI ACCESS_MASK NTAPI
KsQueryObjectAccessMask(
    IN KSOBJECT_HEADER Header);

KSDDKAPI PKSOBJECT_CREATE_ITEM NTAPI
KsQueryObjectCreateItem(
    IN KSOBJECT_HEADER Header);

KSDDKAPI NTSTATUS NTAPI
KsReadFile(
    IN  PFILE_OBJECT FileObject,
    IN  PKEVENT Event OPTIONAL,
    IN  PVOID PortContext OPTIONAL,
    OUT PIO_STATUS_BLOCK IoStatusBlock,
    OUT PVOID Buffer,
    IN  ULONG Length,
    IN  ULONG Key OPTIONAL,
    IN  KPROCESSOR_MODE RequestorMode);

KSDDKAPI VOID NTAPI
KsReleaseIrpOnCancelableQueue(
    IN  PIRP Irp,
    IN  PDRIVER_CANCEL DriverCancel OPTIONAL);

KSDDKAPI PIRP NTAPI
KsRemoveIrpFromCancelableQueue(
    IN  OUT PLIST_ENTRY QueueHead,
    IN  PKSPIN_LOCK SpinLock,
    IN  KSLIST_ENTRY_LOCATION ListLocation,
    IN  KSIRP_REMOVAL_OPERATION RemovalOperation);

KSDDKAPI VOID NTAPI
KsRemoveSpecificIrpFromCancelableQueue(
    IN  PIRP Irp);

KSDDKAPI NTSTATUS NTAPI
KsSetInformationFile(
    IN  PFILE_OBJECT FileObject,
    IN  PVOID FileInformation,
    IN  ULONG Length,
    IN  FILE_INFORMATION_CLASS FileInformationClass);

KSDDKAPI NTSTATUS NTAPI
KsSetMajorFunctionHandler(
    IN  PDRIVER_OBJECT DriverObject,
    IN  ULONG MajorFunction);

KSDDKAPI NTSTATUS NTAPI
KsStreamIo(
    IN  PFILE_OBJECT FileObject,
    IN  PKEVENT Event OPTIONAL,
    IN  PVOID PortContext OPTIONAL,
    IN  PIO_COMPLETION_ROUTINE CompletionRoutine OPTIONAL,
    IN  PVOID CompletionContext OPTIONAL,
    IN  KSCOMPLETION_INVOCATION CompletionInvocationFlags OPTIONAL,
    OUT PIO_STATUS_BLOCK IoStatusBlock,
    IN  OUT PVOID StreamHeaders,
    IN  ULONG Length,
    IN  ULONG Flags,
    IN  KPROCESSOR_MODE RequestorMode);

KSDDKAPI NTSTATUS NTAPI
KsWriteFile(
    IN  PFILE_OBJECT FileObject,
    IN  PKEVENT Event OPTIONAL,
    IN  PVOID PortContext OPTIONAL,
    OUT PIO_STATUS_BLOCK IoStatusBlock,
    IN  PVOID Buffer,
    IN  ULONG Length,
    IN  ULONG Key OPTIONAL,
    IN  KPROCESSOR_MODE RequestorMode);


KSDDKAPI NTSTATUS NTAPI
KsDefaultForwardIrp(
    IN PDEVICE_OBJECT DeviceObject,
    IN PIRP Irp);

/* ===============================================================
    Worker Management Functions
*/

KSDDKAPI NTSTATUS NTAPI
KsRegisterWorker(
    IN  WORK_QUEUE_TYPE WorkQueueType,
    OUT PKSWORKER* Worker);

KSDDKAPI VOID NTAPI
KsUnregisterWorker(
    IN  PKSWORKER Worker);

KSDDKAPI NTSTATUS NTAPI
KsRegisterCountedWorker(
    IN  WORK_QUEUE_TYPE WorkQueueType,
    IN  PWORK_QUEUE_ITEM CountedWorkItem,
    OUT PKSWORKER* Worker);

KSDDKAPI ULONG NTAPI
KsDecrementCountedWorker(
    IN  PKSWORKER Worker);

KSDDKAPI ULONG NTAPI
KsIncrementCountedWorker(
    IN  PKSWORKER Worker);

KSDDKAPI NTSTATUS NTAPI
KsQueueWorkItem(
    IN  PKSWORKER Worker,
    IN  PWORK_QUEUE_ITEM WorkItem);


/* ===============================================================
    Resources / Images
*/

KSDDKAPI NTSTATUS NTAPI
KsLoadResource(
    IN  PVOID ImageBase,
    IN  POOL_TYPE PoolType,
    IN  ULONG_PTR ResourceName,
    IN  ULONG ResourceType,
    OUT PVOID* Resource,
    OUT PULONG ResourceSize);

/* TODO: Implement
KSDDKAPI NTSTATUS NTAPI
KsGetImageNameAndResourceId(
    IN  HANDLE RegKey,
    OUT PUNICODE_STRING ImageName,
    OUT PULONG_PTR ResourceId,
    OUT PULONG ValueType);

KSDDKAPI NTSTATUS NTAPI
KsMapModuleName(
    IN  PDEVICE_OBJECT PhysicalDeviceObject,
    IN  PUNICODE_STRING ModuleName,
    OUT PUNICODE_STRING ImageName,
    OUT PULONG_PTR ResourceId,
    OUT PULONG ValueType);
*/


/* ===============================================================
    Misc. Helper Functions
*/

KSDDKAPI PVOID NTAPI
KsGetNextSibling(
    IN PVOID Object);


KSDDKAPI NTSTATUS NTAPI
KsCacheMedium(
    IN  PUNICODE_STRING SymbolicLink,
    IN  PKSPIN_MEDIUM Medium,
    IN  ULONG PinDirection);

KSDDKAPI NTSTATUS NTAPI
KsDefaultDispatchPnp(
    IN  PDEVICE_OBJECT DeviceObject,
    IN  PIRP Irp);

KSDDKAPI VOID NTAPI
KsSetDevicePnpAndBaseObject(
    IN  KSDEVICE_HEADER Header,
    IN  PDEVICE_OBJECT PnpDeviceObject,
    IN  PDEVICE_OBJECT BaseDevice);

KSDDKAPI NTSTATUS NTAPI
KsDefaultDispatchPower(
    IN  PDEVICE_OBJECT DeviceObject,
    IN  PIRP Irp);

KSDDKAPI VOID NTAPI
KsSetPowerDispatch(
    IN  KSOBJECT_HEADER Header,
    IN  PFNKSCONTEXT_DISPATCH PowerDispatch OPTIONAL,
    IN  PVOID PowerContext OPTIONAL);

KSDDKAPI NTSTATUS NTAPI
KsReferenceBusObject(
    IN  KSDEVICE_HEADER Header);

KSDDKAPI VOID NTAPI
KsDereferenceBusObject(
    IN  KSDEVICE_HEADER Header);

KSDDKAPI NTSTATUS NTAPI
KsFreeObjectCreateItem(
    IN  KSDEVICE_HEADER Header,
    IN  PUNICODE_STRING CreateItem);

KSDDKAPI NTSTATUS NTAPI
KsFreeObjectCreateItemsByContext(
    IN  KSDEVICE_HEADER Header,
    IN  PVOID Context);

KSDDKAPI VOID NTAPI
KsNullDriverUnload(
    IN  PDRIVER_OBJECT DriverObject);

KSDDKAPI PDEVICE_OBJECT NTAPI
KsQueryDevicePnpObject(
    IN  KSDEVICE_HEADER Header);

KSDDKAPI VOID NTAPI
KsRecalculateStackDepth(
    IN  KSDEVICE_HEADER Header,
    IN  BOOLEAN ReuseStackLocation);

KSDDKAPI VOID NTAPI
KsSetTargetDeviceObject(
    IN  KSOBJECT_HEADER Header,
    IN  PDEVICE_OBJECT TargetDevice OPTIONAL);

KSDDKAPI VOID NTAPI
KsSetTargetState(
    IN  KSOBJECT_HEADER Header,
    IN  KSTARGET_STATE TargetState);

KSDDKAPI NTSTATUS NTAPI
KsSynchronousIoControlDevice(
    IN  PFILE_OBJECT FileObject,
    IN  KPROCESSOR_MODE RequestorMode,
    IN  ULONG IoControl,
    IN  PVOID InBuffer,
    IN  ULONG InSize,
    OUT PVOID OutBuffer,
    IN  ULONG OUtSize,
    OUT PULONG BytesReturned);

KSDDKAPI
PKSPIN
NTAPI
KsFilterGetFirstChildPin(
    IN PKSFILTER Filter,
    IN ULONG PinId
);

KSDDKAPI
PFILE_OBJECT
NTAPI
KsPinGetConnectedPinFileObject(
    IN PKSPIN Pin
);

#else

#if !defined( KS_NO_CREATE_FUNCTIONS )

KSDDKAPI
DWORD
WINAPI
KsCreateAllocator(
    IN HANDLE ConnectionHandle,
    IN PKSALLOCATOR_FRAMING AllocatorFraming,
    OUT PHANDLE AllocatorHandle
);

KSDDKAPI
DWORD
NTAPI
KsCreateClock(
    IN HANDLE ConnectionHandle,
    IN PKSCLOCK_CREATE ClockCreate,
    OUT PHANDLE ClockHandle
);

KSDDKAPI
DWORD
WINAPI
KsCreatePin(
    IN HANDLE FilterHandle,
    IN PKSPIN_CONNECT Connect,
    IN ACCESS_MASK DesiredAccess,
    OUT PHANDLE ConnectionHandle
);

KSDDKAPI
DWORD
WINAPI
KsCreateTopologyNode(
    IN HANDLE ParentHandle,
    IN PKSNODE_CREATE NodeCreate,
    IN ACCESS_MASK DesiredAccess,
    OUT PHANDLE NodeHandle
);

#endif

#endif

/* ===============================================================
    AVStream Functions (XP / DirectX 8)
    NOT IMPLEMENTED YET
    http://www.osronline.com/ddkx/stream/avstream_5q9f.htm
*/

#if defined(_NTDDK_)

KSDDKAPI
NTSTATUS
NTAPI
KsMergeAutomationTables(
    OUT PKSAUTOMATION_TABLE* AutomationTableAB,
    IN PKSAUTOMATION_TABLE AutomationTableA OPTIONAL,
    IN PKSAUTOMATION_TABLE AutomationTableB OPTIONAL,
    IN KSOBJECT_BAG Bag OPTIONAL
);

KSDDKAPI
NTSTATUS
NTAPI
KsInitializeDriver(
    IN PDRIVER_OBJECT  DriverObject,
    IN PUNICODE_STRING  RegistryPath,
    IN const KSDEVICE_DESCRIPTOR  *Descriptor OPTIONAL);

typedef struct _KSFILTERFACTORY KSFILTERFACTORY, *PKSFILTERFACTORY; //FIXME



KSDDKAPI
NTSTATUS
NTAPI
KsInitializeDevice(
    IN PDEVICE_OBJECT  FunctionalDeviceObject,
    IN PDEVICE_OBJECT  PhysicalDeviceObject,
    IN PDEVICE_OBJECT  NextDeviceObject,
    IN const KSDEVICE_DESCRIPTOR*  Descriptor OPTIONAL);


typedef void (NTAPI *PFNKSFILTERFACTORYPOWER)(
    IN  PKSFILTERFACTORY FilterFactory,
    IN  DEVICE_POWER_STATE State);

KSDDKAPI
NTSTATUS
NTAPI
_KsEdit(
    IN  KSOBJECT_BAG ObjectBag,
    IN  OUT PVOID* PointerToPointerToItem,
    IN  ULONG NewSize,
    IN  ULONG OldSize,
    IN  ULONG Tag);

KSDDKAPI
VOID
NTAPI
KsAcquireControl(
    IN  PVOID Object);

KSDDKAPI
VOID
NTAPI
KsAcquireDevice(
    IN  PKSDEVICE Device);

KSDDKAPI
NTSTATUS
NTAPI
KsAddDevice(
    IN  PDRIVER_OBJECT DriverObject,
    IN  PDEVICE_OBJECT PhysicalDeviceObject);

KSDDKAPI
VOID
NTAPI
KsAddEvent(
    IN  PVOID Object,
    IN  PKSEVENT_ENTRY EventEntry);

KSDDKAPI
NTSTATUS
NTAPI
KsAddItemToObjectBag(
    IN  KSOBJECT_BAG ObjectBag,
    IN  PVOID Item,
    IN  PFNKSFREE Free OPTIONAL);

KSDDKAPI
ULONG
NTAPI
KsRemoveItemFromObjectBag(
    IN KSOBJECT_BAG ObjectBag,
    IN PVOID Item,
    IN BOOLEAN Free);

KSDDKAPI
NTSTATUS
NTAPI
KsAllocateObjectBag(
    IN  PKSDEVICE Device,
    OUT KSOBJECT_BAG* ObjectBag);

KSDDKAPI
VOID
NTAPI
KsFreeObjectBag(
    IN KSOBJECT_BAG ObjectBag
);

KSDDKAPI
VOID
NTAPI
KsCompletePendingRequest(
    IN  PIRP Irp);

KSDDKAPI
NTSTATUS
NTAPI
KsCopyObjectBagItems(
    IN  KSOBJECT_BAG ObjectBagDestination,
    IN  KSOBJECT_BAG ObjectBagSource);

KSDDKAPI
NTSTATUS
NTAPI
KsCreateDevice(
    IN  PDRIVER_OBJECT DriverObject,
    IN  PDEVICE_OBJECT PhysicalDeviceObject,
    IN  const KSDEVICE_DESCRIPTOR* Descriptor OPTIONAL,
    IN  ULONG ExtensionSize OPTIONAL,
    OUT PKSDEVICE* Device OPTIONAL);

KSDDKAPI
NTSTATUS
NTAPI
KsCreateFilterFactory(
    IN  PDEVICE_OBJECT DeviceObject,
    IN  const KSFILTER_DESCRIPTOR* Descriptor,
    IN  PWCHAR RefString OPTIONAL,
    IN  PSECURITY_DESCRIPTOR SecurityDescriptor OPTIONAL,
    IN  ULONG CreateItemFlags,
    IN  PFNKSFILTERFACTORYPOWER SleepCallback OPTIONAL,
    IN  PFNKSFILTERFACTORYPOWER WakeCallback OPTIONAL,
    OUT PKSFILTERFACTORY *FilterFactory OPTIONAL);

KSDDKAPI
NTSTATUS
NTAPI
KsFilterFactorySetDeviceClassesState(
    IN PKSFILTERFACTORY FilterFactory,
    IN BOOLEAN NewState
);

KSDDKAPI
NTSTATUS
NTAPI
KsFilterFactoryUpdateCacheData(
    IN PKSFILTERFACTORY FilterFactory,
    IN const KSFILTER_DESCRIPTOR *FilterDescriptor OPTIONAL
);

KSDDKAPI
PKSPIN
NTAPI
KsGetPinFromIrp(
    IN PIRP Irp
);

KSDDKAPI
PKSFILTER
NTAPI
KsGetFilterFromIrp(
    IN PIRP Irp
);

KSDDKAPI
NTSTATUS
NTAPI
KsDefaultAddEventHandler(
    IN  PIRP Irp,
    IN  PKSEVENTDATA EventData,
    IN  OUT PKSEVENT_ENTRY EventEntry);

KSDDKAPI
NTSTATUS
NTAPI
KsDispatchQuerySecurity(
    IN PDEVICE_OBJECT DeviceObject,
    IN PIRP Irp
);

KSDDKAPI
NTSTATUS
NTAPI
KsDispatchSetSecurity(
    IN PDEVICE_OBJECT DeviceObject,
    IN PIRP Irp
);

KSDDKAPI
PVOID
NTAPI
KsGetParent(
    IN PVOID Object
);


static
PKSFILTERFACTORY
__inline
KsFilterGetParentFilterFactory(
    IN PKSFILTER Filter
)
{
    return (PKSFILTERFACTORY) KsGetParent((PVOID) Filter);
}

static
PKSDEVICE
__inline
KsFilterFactoryGetParentDevice(
    IN PKSFILTERFACTORY FilterFactory
)
{
    return (PKSDEVICE) KsGetParent((PVOID) FilterFactory);
}



#define KsDeleteFilterFactory(FilterFactory)                                           \
    KsFreeObjectCreateItemsByContext(                                          \
            *(KSDEVICE_HEADER *)(                                                      \
                    KsFilterFactoryGetParentDevice(FilterFactory)->FunctionalDeviceObject->    \
                    DeviceExtension),                                                          \
            FilterFactory)

KSDDKAPI
ULONG
NTAPI
KsDeviceGetBusData(
    IN  PKSDEVICE Device,
    IN  ULONG DataType,
    IN  PVOID Buffer,
    IN  ULONG Offset,
    IN  ULONG Length);


KSDDKAPI
PVOID
NTAPI
KsGetFirstChild(
    IN PVOID Object
);

KSDDKAPI
PKSFILTERFACTORY
NTAPI
KsDeviceGetFirstChildFilterFactory(
    IN  PKSDEVICE Device);

#if defined(_UNKNOWN_H_) || defined(__IUnknown_INTERFACE_DEFINED__)

KSDDKAPI
PUNKNOWN
NTAPI
KsGetOuterUnknown(
    IN PVOID Object
);

static
__inline
PUNKNOWN
KsDeviceGetOuterUnknown(
    IN  PKSDEVICE Device)
{
    return KsGetOuterUnknown((PVOID) Device);
}

KSDDKAPI
PUNKNOWN
NTAPI
KsDeviceRegisterAggregatedClientUnknown(
    IN  PKSDEVICE Device,
    IN  PUNKNOWN ClientUnknown);


#endif

#if defined(_UNKNOWN_H_) || defined(__IUnknown_INTERFACE_DEFINED__)

typedef interface IKsReferenceClock* PIKSREFERENCECLOCK;

#undef INTERFACE
#define INTERFACE IKsReferenceClock
DECLARE_INTERFACE_(IKsReferenceClock, IUnknown)
{
    DEFINE_ABSTRACT_UNKNOWN() // For C
    STDMETHOD_(LONGLONG, GetTime)(THIS
                                 ) PURE;
    STDMETHOD_(LONGLONG, GetPhysicalTime)(THIS
                                         ) PURE;
    STDMETHOD_(LONGLONG, GetCorrelatedTime)(THIS_
                                            OUT PLONGLONG SystemTime
                                           ) PURE;
    STDMETHOD_(LONGLONG, GetCorrelatedPhysicalTime)(THIS_
            OUT PLONGLONG SystemTime
                                                   ) PURE;
    STDMETHOD_(NTSTATUS, GetResolution)(THIS_
                                        OUT PKSRESOLUTION Resolution
                                       ) PURE;
    STDMETHOD_(NTSTATUS, GetState)(THIS_
                                   OUT PKSSTATE State
                                  ) PURE;
};

#undef INTERFACE
#define INTERFACE IKsControl

DEFINE_GUID(IID_IKsControl, 0x28F54685L, 0x06FD, 0x11D2, 0xB2, 0x7A, 0x00, 0xA0, 0xC9, 0x22, 0x31, 0x96);

DECLARE_INTERFACE_(IKsControl, IUnknown)
{
    STDMETHOD_(NTSTATUS, QueryInterface)(THIS_
                                         REFIID InterfaceId,
                                         PVOID * Interface)PURE;
    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;
    STDMETHOD_(NTSTATUS, KsProperty)(THIS_
                                     IN PKSPROPERTY Property,
                                     IN ULONG PropertyLength,
                                     IN OUT PVOID PropertyData,
                                     IN ULONG DataLength,
                                     OUT ULONG * BytesReturned
                                    ) PURE;
    STDMETHOD_(NTSTATUS, KsMethod)(THIS_
                                   IN PKSMETHOD Method,
                                   IN ULONG MethodLength,
                                   IN OUT PVOID MethodData,
                                   IN ULONG DataLength,
                                   OUT ULONG * BytesReturned
                                  ) PURE;
    STDMETHOD_(NTSTATUS, KsEvent)(THIS_
                                  IN PKSEVENT Event OPTIONAL,
                                  IN ULONG EventLength,
                                  IN OUT PVOID EventData,
                                  IN ULONG DataLength,
                                  OUT ULONG * BytesReturned
                                 ) PURE;
};

#undef INTERFACE
typedef IKsControl* PIKSCONTROL;

#endif

KSDDKAPI
VOID
NTAPI
KsDeviceRegisterAdapterObject(
    IN  PKSDEVICE Device,
    IN  PADAPTER_OBJECT AdapterObject,
    IN  ULONG MaxMappingByteCount,
    IN  ULONG MappingTableStride);

KSDDKAPI
ULONG
NTAPI
KsDeviceSetBusData(
    IN  PKSDEVICE Device,
    IN  ULONG DataType,
    IN  PVOID Buffer,
    IN  ULONG Offset,
    IN  ULONG Length);


KSDDKAPI
VOID
NTAPI
KsReleaseControl(
    IN PVOID Object
);

#define KsDiscard(object, pointer) \
    KsRemoveItemFromObjectBag(object->Bag, pointer, TRUE)

#define KsFilterAcquireControl(Filter) \
    KsAcquireControl((PVOID) Filter);

#define KsFilterReleaseControl(Filter) \
    KsReleaseControl((PVOID) Filter);

#define KsFilterAddEvent(Filter, EventEntry) \
    KsAddEvent(Filter,EventEntry);

KSDDKAPI
VOID
NTAPI
KsFilterAcquireProcessingMutex(
    IN  PKSFILTER Filter);


KSDDKAPI
NTSTATUS
NTAPI
KsFilterAddTopologyConnections(
    IN  PKSFILTER Filter,
    IN  ULONG NewConnectionsCount,
    IN  const KSTOPOLOGY_CONNECTION *const NewTopologyConnections);

KSDDKAPI
VOID
NTAPI
KsFilterAttemptProcessing(
    IN  PKSFILTER Filter,
    IN  BOOLEAN Asynchronous);

KSDDKAPI
NTSTATUS
NTAPI
KsFilterCreateNode(
    IN  PKSFILTER Filter,
    IN  const KSNODE_DESCRIPTOR *const NodeDescriptor,
    OUT PULONG NodeID);

KSDDKAPI
NTSTATUS
NTAPI
KsFilterCreatePinFactory(
    IN  PKSFILTER Filter,
    IN  const KSPIN_DESCRIPTOR_EX *const PinDescriptor,
    OUT PULONG PinID);

KSDDKAPI
PKSDEVICE
__inline
KsFilterFactoryGetDevice(
    IN  PKSFILTERFACTORY FilterFactory);

/* etc. */
#endif /* avstream */

#ifdef __cplusplus
}
#endif

#endif
