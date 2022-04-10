main:main.o admin.o buyer.o calculator.o file.o helper.o login_and_register.o personal.o seller.o sql_coping.o admin.h buyer.h calculator.h seller.h sql_coping.h trading_platform.h
	g++ main.o admin.o buyer.o calculator.o file.o helper.o login_and_register.o personal.o seller.o sql_coping.o admin.h buyer.h calculator.h seller.h sql_coping.h trading_platform.h -o main
main.o:main.cpp
	g++ -c main.cpp -o main.o
admin.o:admin.cpp
	g++ -c  admin.cpp -o admin.o
buyer.o:buyer.cpp
	g++ -c buyer.cpp -o buyer.o
calculator.o:calculator.cpp
	g++ -c calculator.cpp -o calculator.o
file.o:file.cpp
	g++ -c file.cpp -o file.o
helper.o:helper.cpp
	g++ -c helper.cpp -o helper.o
login_and_register.o:login_and_register.cpp
	g++ -c login_and_register.cpp -o login_and_register.o
personal.o:personal.cpp
	g++ -c personal.cpp -o personal.o
seller.o:seller.cpp
	g++ -c seller.cpp -o seller.o
sql_coping.o:sql_coping.cpp
	g++ -c sql_coping.cpp -o sql_coping.o

clean:
	rm *.o
	rm main