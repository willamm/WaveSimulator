/****************************************************************************
** Resource object code
**
** Created by: The Resource Compiler for Qt version 5.6.2
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

static const unsigned char qt_resource_data[] = {
  // C:/Users/Will/Documents/WaveSimulator/WaveSim/WaveSim/default.txt
  0x0,0x0,0x0,0x38,
  0x46,
  0x69,0x72,0x73,0x74,0x20,0x52,0x6f,0x77,0x9,0x52,0x6f,0x6f,0x74,0xd,0xa,0x20,
  0x53,0x65,0x63,0x6f,0x6e,0x64,0x20,0x43,0x6f,0x6c,0x75,0x6d,0x6e,0x9,0x54,0x65,
  0x73,0x74,0xd,0xa,0x20,0x20,0x54,0x68,0x69,0x72,0x64,0x20,0x43,0x6f,0x6c,0x75,
  0x6d,0x6e,0x9,0x54,0x65,0x73,0x74,
  
};

static const unsigned char qt_resource_name[] = {
  // default.txt
  0x0,0xb,
  0xc,0xe2,0x22,0xf4,
  0x0,0x64,
  0x0,0x65,0x0,0x66,0x0,0x61,0x0,0x75,0x0,0x6c,0x0,0x74,0x0,0x2e,0x0,0x74,0x0,0x78,0x0,0x74,
  
};

static const unsigned char qt_resource_struct[] = {
  // :
  0x0,0x0,0x0,0x0,0x0,0x2,0x0,0x0,0x0,0x1,0x0,0x0,0x0,0x1,
  // :/default.txt
  0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x1,0x0,0x0,0x0,0x0,

};

#ifdef QT_NAMESPACE
#  define QT_RCC_PREPEND_NAMESPACE(name) ::QT_NAMESPACE::name
#  define QT_RCC_MANGLE_NAMESPACE0(x) x
#  define QT_RCC_MANGLE_NAMESPACE1(a, b) a##_##b
#  define QT_RCC_MANGLE_NAMESPACE2(a, b) QT_RCC_MANGLE_NAMESPACE1(a,b)
#  define QT_RCC_MANGLE_NAMESPACE(name) QT_RCC_MANGLE_NAMESPACE2( \
        QT_RCC_MANGLE_NAMESPACE0(name), QT_RCC_MANGLE_NAMESPACE0(QT_NAMESPACE))
#else
#   define QT_RCC_PREPEND_NAMESPACE(name) name
#   define QT_RCC_MANGLE_NAMESPACE(name) name
#endif

#ifdef QT_NAMESPACE
namespace QT_NAMESPACE {
#endif

bool qRegisterResourceData(int, const unsigned char *, const unsigned char *, const unsigned char *);

bool qUnregisterResourceData(int, const unsigned char *, const unsigned char *, const unsigned char *);

#ifdef QT_NAMESPACE
}
#endif

int QT_RCC_MANGLE_NAMESPACE(qInitResources_WaveSim)();
int QT_RCC_MANGLE_NAMESPACE(qInitResources_WaveSim)()
{
    QT_RCC_PREPEND_NAMESPACE(qRegisterResourceData)
        (0x01, qt_resource_struct, qt_resource_name, qt_resource_data);
    return 1;
}

int QT_RCC_MANGLE_NAMESPACE(qCleanupResources_WaveSim)();
int QT_RCC_MANGLE_NAMESPACE(qCleanupResources_WaveSim)()
{
    QT_RCC_PREPEND_NAMESPACE(qUnregisterResourceData)
       (0x01, qt_resource_struct, qt_resource_name, qt_resource_data);
    return 1;
}

namespace {
   struct initializer {
       initializer() { QT_RCC_MANGLE_NAMESPACE(qInitResources_WaveSim)(); }
       ~initializer() { QT_RCC_MANGLE_NAMESPACE(qCleanupResources_WaveSim)(); }
   } dummy;
}
