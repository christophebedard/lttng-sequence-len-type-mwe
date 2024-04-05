APP_NAME= myapp
LINKED_LIBRARIES= -ldl
LIB_NAME= mytps
LIB_DIR= ${PWD}/../lib

all: ${APP_NAME}

${APP_NAME}: ${APP_NAME}.o
	gcc -o $@ $< -L${LIB_DIR} -Wl,-rpath=${LIB_DIR} -l${LIB_NAME} ${LINKED_LIBRARIES}

${APP_NAME}.o: ${APP_NAME}.c
	gcc -I${LIB_DIR} -c $<

clean:
	rm -f ${APP_NAME}
	rm -f ${APP_NAME}.o
