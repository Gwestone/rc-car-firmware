idf_component_register( SRCS "main.c"
                        INCLUDE_DIRS "."

                        SRCS "lib/event/event.c"
                        INCLUDE_DIRS "lib/event"

                        SRCS "lib/fs/fs.c"
                        INCLUDE_DIRS "lib/fs"

                        SRCS "lib/http/http.c"
                        INCLUDE_DIRS "lib/http"

                        SRCS "lib/wifi/wifi.c"
                        INCLUDE_DIRS "lib/wifi"
)
