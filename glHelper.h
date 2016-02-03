#ifndef __GL_HELPER_H__
#define __GL_HELPER_H__

#ifdef __ANDROID__
#include <android/log.h>
#define GL_LOG(fmt, ...) __android_log_print(ANDROID_LOG_INFO, "glHelper", fmt, ## __VA_ARGS__)
#else
#define GL_LOG(fmt, ...) fprintf(stderr, fmt, ## __VA_ARGS__)
#endif

/* GL ErrorCode */
#if !defined(__gl_h_) && !defined(__gl2_h_) && !defined(__gl3_h_)
#define GL_NO_ERROR                       0
#define GL_INVALID_ENUM                   0x0500
#define GL_INVALID_VALUE                  0x0501
#define GL_INVALID_OPERATION              0x0502
#define GL_OUT_OF_MEMORY                  0x0505
#endif
#if !defined(__gl_h_)
#define GL_STACK_OVERFLOW                 0x0503	// <= gl1.1
#define GL_STACK_UNDERFLOW                0x0504	// <= gl1.1
#endif
#if !defined(__gl2_h_) && !defined(__gl3_h_)
#define GL_INVALID_FRAMEBUFFER_OPERATION  0x0506	// >= gl2
#endif

/* EGL ErrorCode */
#if !defined(__egl_h_)
#define EGL_SUCCESS				0x3000
#define EGL_NOT_INITIALIZED		0x3001
#define EGL_BAD_ACCESS			0x3002
#define EGL_BAD_ALLOC			0x3003
#define EGL_BAD_ATTRIBUTE		0x3004
#define EGL_BAD_CONFIG			0x3005
#define EGL_BAD_CONTEXT			0x3006
#define EGL_BAD_CURRENT_SURFACE	0x3007
#define EGL_BAD_DISPLAY			0x3008
#define EGL_BAD_MATCH			0x3009
#define EGL_BAD_NATIVE_PIXMAP	0x300A
#define EGL_BAD_NATIVE_WINDOW	0x300B
#define EGL_BAD_PARAMETER		0x300C
#define EGL_BAD_SURFACE			0x300D
#define EGL_CONTEXT_LOST		0x300E	/* EGL 1.1 - IMG_power_management */
/* Reserved 0x300F-0x301F for additional errors */
#endif

#define _CASE(x) if (x == code) {str = #x;}

#define GL_STR_ERROR(err) ({					\
	unsigned int code = err;					\
	unsigned char* str = "GL unknow error";		\
	_CASE(GL_INVALID_ENUM);						\
	_CASE(GL_INVALID_VALUE);					\
	_CASE(GL_INVALID_OPERATION);				\
	_CASE(GL_STACK_OVERFLOW);       			\
	_CASE(GL_STACK_UNDERFLOW);              	\
	_CASE(GL_OUT_OF_MEMORY);                	\
	_CASE(GL_INVALID_FRAMEBUFFER_OPERATION);	\
	str;										\
})

#define EGL_STR_ERROR(err) ({					\
	unsigned int code = err;					\
	unsigned char* str = "EGL unknow error";	\
	_CASE(EGL_NOT_INITIALIZED);					\
	_CASE(EGL_BAD_ACCESS);						\
	_CASE(EGL_BAD_ALLOC);						\
	_CASE(EGL_BAD_ATTRIBUTE);					\
	_CASE(EGL_BAD_CONFIG);						\
	_CASE(EGL_BAD_CONTEXT);						\
	_CASE(EGL_BAD_CURRENT_SURFACE);				\
	_CASE(EGL_BAD_DISPLAY);						\
	_CASE(EGL_BAD_MATCH);						\
	_CASE(EGL_BAD_NATIVE_PIXMAP);				\
	_CASE(EGL_BAD_NATIVE_WINDOW);				\
	_CASE(EGL_BAD_PARAMETER);					\
	_CASE(EGL_BAD_SURFACE);						\
	_CASE(EGL_CONTEXT_LOST);					\
	str;										\
})

#define EGL_CALL(func) func; ({									\
	EGLint error = eglGetError();								\
	while (error != EGL_SUCCESS) {								\
        GL_LOG("file: %s line: %d eglError %s (0x%x)\n",		\
			__FILE__, __LINE__, EGL_STR_ERROR(error), error);	\
		error = eglGetError();									\
    }															\
})

#define GL_CALL(func) func; ({									\
	GLint error = glGetError();									\
    while (error != GL_NO_ERROR) {								\
        GL_LOG("file: %s line: %d glError %s (0x%x)\n",			\
			__FILE__, __LINE__, GL_STR_ERROR(error), error);	\
		error = glGetError();									\
    }															\
})

#endif	/* __GL_HELPER_H__ */
