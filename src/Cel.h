/* Cel.h
 *
 */

#if !defined CEL_H
#define CEL_H

#if defined __cplusplus
extern "C" {
#endif //__cplusplus

typedef struct {
	unsigned int x;		//!< X position of top-left corner of cel
	unsigned int y;		//!< Y position of top-left corner of cel
	unsigned int w;		//!< Width of cel
	unsigned int h;		//!< Height of cel
} Cel;

#if defined __cplusplus
}
#endif //__cplusplus

#endif //CEL_H
