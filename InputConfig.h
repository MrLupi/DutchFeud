// the configured options and settings for ToastFeud
#define ToastFeudServer_VERSION_MAJOR @DutchFeudServer_VERSION_MAJOR@
#define ToastFeudServer_VERSION_MINOR @DutchFeudServer_VERSION_MINOR@

#define QU(x) #x
#define QUH(x) QU(x)
#define VERSION_STRING "v" QUH(ToastFeudServer_VERSION_MAJOR) "." QUH(ToastFeudServer_VERSION_MINOR)