// Auto-generated with: android/scripts/gen-entries.py --mode=functions host/gl/OpenGLESDispatch/render_egl_extensions.entries --output=include/OpenGLESDispatch/RenderEGL_extensions_functions.h
// DO NOT EDIT THIS FILE

#ifndef RENDER_EGL_EXTENSIONS_FUNCTIONS_H
#define RENDER_EGL_EXTENSIONS_FUNCTIONS_H

#include <EGL/egl.h>
#define EGL_EGLEXT_PROTOTYPES
#include <EGL/eglext.h>
#define LIST_RENDER_EGL_EXTENSIONS_FUNCTIONS(X) \
  X(EGLImageKHR, eglCreateImageKHR, (EGLDisplay display, EGLContext context, EGLenum target, EGLClientBuffer buffer, const EGLint* attrib_list)) \
  X(EGLBoolean, eglDestroyImageKHR, (EGLDisplay display, EGLImageKHR image)) \
  X(EGLSyncKHR, eglCreateSyncKHR, (EGLDisplay display, EGLenum type, const EGLint* attribs)) \
  X(EGLint, eglClientWaitSyncKHR, (EGLDisplay display, EGLSyncKHR sync, EGLint flags, EGLTimeKHR timeout)) \
  X(EGLint, eglWaitSyncKHR, (EGLDisplay display, EGLSyncKHR sync, EGLint flags)) \
  X(EGLBoolean, eglDestroySyncKHR, (EGLDisplay display, EGLSyncKHR sync)) \
  X(EGLint, eglGetMaxGLESVersion, (EGLDisplay display)) \
  X(void, eglBlitFromCurrentReadBufferANDROID, (EGLDisplay display, EGLImageKHR image)) \
  X(void*, eglSetImageFenceANDROID, (EGLDisplay display, EGLImageKHR image)) \
  X(void, eglWaitImageFenceANDROID, (EGLDisplay display, void* fence)) \
  X(void, eglAddLibrarySearchPathANDROID, (const char* path)) \
  X(EGLBoolean, eglQueryVulkanInteropSupportANDROID, ()) \
  X(EGLBoolean, eglGetSyncAttribKHR, (EGLDisplay display, EGLSync sync, EGLint attribute, EGLint * value)) \
  X(EGLDisplay, eglGetNativeDisplayANDROID, (EGLDisplay display)) \
  X(EGLContext, eglGetNativeContextANDROID, (EGLDisplay display, EGLContext context)) \
  X(EGLImage, eglGetNativeImageANDROID, (EGLDisplay display, EGLImage image)) \
  X(EGLBoolean, eglSetImageInfoANDROID, (EGLDisplay display, EGLImage image, EGLint width, EGLint height, EGLint internalformat)) \
  X(EGLImage, eglImportImageANDROID, (EGLDisplay display, EGLImage image)) \
  X(EGLint, eglDebugMessageControlKHR, (EGLDEBUGPROCKHR callback, const EGLAttrib * attrib_list)) \
  X(EGLBoolean, eglSetNativeTextureDecompressionEnabledANDROID, (EGLDisplay display, EGLBoolean enabled)) \
  X(EGLBoolean, eglSetProgramBinaryLinkStatusEnabledANDROID, (EGLDisplay display, EGLBoolean enabled)) \

EGLAPI EGLint EGLAPIENTRY eglGetMaxGLESVersion(EGLDisplay display);
EGLAPI void EGLAPIENTRY eglBlitFromCurrentReadBufferANDROID(EGLDisplay display, EGLImageKHR image);
EGLAPI void* EGLAPIENTRY eglSetImageFenceANDROID(EGLDisplay display, EGLImageKHR image);
EGLAPI void EGLAPIENTRY eglWaitImageFenceANDROID(EGLDisplay display, void* fence);
EGLAPI void EGLAPIENTRY eglAddLibrarySearchPathANDROID(const char* path);
EGLAPI EGLBoolean EGLAPIENTRY eglQueryVulkanInteropSupportANDROID();

#endif  // RENDER_EGL_EXTENSIONS_FUNCTIONS_H
