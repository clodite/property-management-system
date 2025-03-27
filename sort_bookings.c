#include "header.h"
#include "function.h"
#include "struct.h"

// 按条件排序预约：

// 增/减/不排序/1/-1/0
// 排序条件：1.book_id 2.入住时间 3.居住多久 4.预约人id 5.预约状态

struct strbook* sort_bookings(int type_x, int order_x, int type_y, int order_y)
{
    struct strbook* raw_bookings = view_bookings(-1, -1, -1, -1, "-1", -1);

}
