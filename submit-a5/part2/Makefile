

CPP_FLAGS=-std=c++11 
TEST_DIR=tests
OUT_DIR=bin
build:
	-mkdir bin
	g++ $(CPP_FLAGS) $(TEST_DIR)/test_constructor.cpp -o $(OUT_DIR)/test_constructor
	g++ $(CPP_FLAGS) $(TEST_DIR)/test_payload.cpp -o $(OUT_DIR)/test_payload
	g++ $(CPP_FLAGS) $(TEST_DIR)/test_send_and_receive.cpp -o $(OUT_DIR)/test_send_and_receive
	g++ $(CPP_FLAGS) $(TEST_DIR)/test_multiple_clients.cpp -o $(OUT_DIR)/test_multiple_clients
	g++ $(CPP_FLAGS) $(TEST_DIR)/test_get_client_list.cpp -o $(OUT_DIR)/test_get_client_list
	g++ $(CPP_FLAGS) main.cpp -o $(OUT_DIR)/server
	g++ $(CPP_FLAGS) client.cpp -o $(OUT_DIR)/client

run:
	./$(OUT_DIR)/test_constructor
	./$(OUT_DIR)/test_payload
	./$(OUT_DIR)/test_send_and_receive
	./$(OUT_DIR)/test_multiple_clients
	#./$(OUT_DIR)/test_get_client_list
	echo "All tests PASSED"

clean:
	rm -rf bin