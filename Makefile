FLAGS = -D _DEBUG -ggdb3 -std=c++17 -O0 -Wall -Wextra -Weffc++ -Waggressive-loop-optimizations -Wc++14-compat                    \
-Wmissing-declarations -Wcast-align -Wcast-qual -Wchar-subscripts -Wconditionally-supported -Wconversion -Wctor-dtor-privacy     \
-Wempty-body -Wfloat-equal -Wformat-nonliteral -Wformat-security -Wformat-signedness -Wformat=2 -Winline -Wlogical-op            \
-Wnon-virtual-dtor -Wopenmp-simd -Woverloaded-virtual -Wpacked -Wpointer-arith -Winit-self -Wredundant-decls -Wshadow            \
-Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=2 -Wsuggest-attribute=noreturn                           \
-Wsuggest-final-methods -Wsuggest-final-types -Wsuggest-override -Wswitch-default -Wswitch-enum -Wsync-nand -Wundef              \
-Wunreachable-code -Wunused -Wuseless-cast -Wvariadic-macros -Wno-literal-suffix -Wno-missing-field-initializers                 \
-Wno-narrowing -Wno-old-style-cast -Wno-varargs -Wstack-protector -fcheck-new -fsized-deallocation -fstack-protector             \
-fstrict-overflow -flto-odr-type-merging -fno-omit-frame-pointer -Wlarger-than=8192 -Wstack-usage=8192 -pie -fPIE -Werror=vla    \
-fsanitize=address,alignment,bool,bounds,enum,float-cast-overflow,float-divide-by-zero,integer-divide-by-zero,leak,nonnull-attribute,null,return,returns-nonnull-attribute,shift,signed-integer-overflow,undefined,unreachable,vla-bound,vptr         

# TODO BUILD_FOLDER = objects

# TODO OBJECT_FILES = main.o utilits.o stack_implementation.o
# $(addprefix, BUILD_FOLDER, OBJECT_FILES)

# TODO https://makefiletutorial.com/ - static pattern rules

Compile: ./objects/main.o ./objects/utilits.o ./objects/stack_implementation.o
	g++ ./objects/main.o ./objects/utilits.o ./objects/stack_implementation.o $(FLAGS) -o app 
./objects/main.o : src/main.cpp 
	g++ -c src/main.cpp -o ./objects/main.o

./objects/utilits.o : src/utilits.cpp headers/utilits.h    
	g++ -c src/utilits.cpp -o ./objects/utilits.o 

./objects/stack_implementation.o : src/stack_implementation.cpp headers/stack_implementation.h
	g++ -c src/stack_implementation.cpp -o ./objects/stack_implementation.o

clean:    
	rm ./objects/*.o app