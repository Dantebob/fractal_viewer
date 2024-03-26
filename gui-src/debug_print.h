#ifndef _DEBUG_PRINT_H_
#define _DEBUG_PRINT_H_

#if DEBUG_LEVEL > 2
#define DEBUG_PRINT(msg) std::cout << __FILE__ << ":" << __LINE__ << " " << msg
#else
#define DEBUG_PRINT(msg)
#endif

#endif /* _DEBUG_PRINT_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */