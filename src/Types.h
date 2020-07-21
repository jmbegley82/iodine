/* Types.h
 *
 */

#if !defined TYPES_H
#define TYPES_H

#if defined __cplusplus
extern "C" {
#endif //__cplusplus

struct _coords {
	double x;		//<! X coordinate
	double y;		//<! Y coordinate
};

typedef struct _coords coords;	//<! A pair of doubles, useful for describing coordinates

#if defined __cplusplus
}
#endif //__cplusplus

#endif //TYPES_H
