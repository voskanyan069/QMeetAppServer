#ifndef __SERVER_REST_ROUTES_HXX__
#define __SERVER_REST_ROUTES_HXX__

#define API_BASE                "/api"
#define API_VERSION             "/v1"
#define ROUTE_ROOT              API_BASE API_VERSION

#define ROUTE_MEETING           ROUTE_ROOT      "/meeting"
#define ROUTE_CREATE_MEETING    ROUTE_MEETING   "/create"
#define ROUTE_CHECK_MEET_EXISTS ROUTE_MEETING   "/is_exists"

#define ROUTE_ACCOUNT           ROUTE_ROOT      "/account"
#define ROUTE_CREATE_ACCOUNT    ROUTE_ACCOUNT   "/create"
#define ROUTE_CHECK_USER_EXISTS ROUTE_ACCOUNT   "/is_exists"

#endif // ! __SERVER_REST_ROUTES_HXX__
