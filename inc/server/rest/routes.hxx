#ifndef __SERVER_REST_ROUTES_HXX__
#define __SERVER_REST_ROUTES_HXX__

#define API_BASE                "/api"
#define API_VERSION             "/v1"
#define ROUTE_ROOT              API_BASE API_VERSION

#define ROUTE_MEETING           ROUTE_ROOT "/meeting"
#define ROUTE_JOIN_MEETING      ROUTE_MEETING "/join"
#define ROUTE_CREATE_MEETING    ROUTE_MEETING "/create"
#define ROUTE_GET_MEETING_ROOMS ROUTE_MEETING "/get"

#define ROUTE_ACCOUNT           ROUTE_ROOT "/account"
#define ROUTE_CREATE_ACCOUNT    ROUTE_ACCOUNT "/create"
#define ROUTE_CHECK_USER_EXISTS ROUTE_ACCOUNT "/is_exists"

#endif // ! __SERVER_REST_ROUTES_HXX__
