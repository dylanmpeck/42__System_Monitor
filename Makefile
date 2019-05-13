NAME = ft_gkrellm

GUISOURCE = CPUInfoModule.cpp \
			CPUModule.cpp \
			DateTimeModule.cpp \
			GraphicsDisplay.cpp \
			HostnameModule.cpp \
			NetModule.cpp \
			OSModule.cpp \
			RamModule.cpp \
			UsernameModule.cpp \
			guiMain.cpp \
			helper.cpp
GUIOBJ = $(subst .cpp,.o, $(GUISOURCE))

TEXTSOURCE = TextDisplay.cpp \
			 helper.cpp \
			 textMain.cpp
TEXTOBJ = $(subst .cpp,.o, $(TEXTSOURCE))

all: text

gui:
	clang++ -c -Wall -Wextra -Werror $(GUISOURCE) -I SDL2/include
	clang++ -Wall -Wextra -Werror $(GUIOBJ) -o $(NAME) -I SDL2/include -L SDL2/lib -lSDL2-2.0.0 -lSDL2_ttf-2.0.0

text:
	clang++ -c -Wall -Wextra -Werror $(TEXTSOURCE)
	clang++ -Wall -Wextra -Werror $(TEXTOBJ) -o $(NAME) -lcurses

clean:
	/bin/rm -f *.o

fclean: clean
	/bin/rm $(NAME)

re: fclean all
