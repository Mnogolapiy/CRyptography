#include <iostream>
#include <string>
#include <fstream>
#include <vector>

int main(int argc, const char *argv[]) {
    if (argc != 3) {
        std::cerr << "Error: Use three parameters\n";
        return 5;
    }
    const std::string mode(argv[1]); // Режим работы
    const std::string file_name(argv[2]); // Имя файла


    if (mode == "encryption") {
        // Режим шифрование
        std::cout << "Input message:";
        std::string message;
        getline(std::cin, message);
        std::cout << " " << std::endl;
        std::cout << "Input key:";
        int key;
        std::cin >> key;
        const char *data = message.data();
        size_t size = message.size();
        std::vector<char> bytes(size);
        for (int i = 0; i < size; i++) {
            bytes[i] = data[i];
        }
        srand(key);
        std::ofstream outputFile;
        outputFile.open(file_name, std::ios::binary);
        outputFile.clear();
        for (int i = 0; i < bytes.size(); ++i) {
            unsigned int gamma = rand();
            unsigned int message_xored_with_gamma =
                    (static_cast<unsigned int>(bytes[i])) ^ gamma;
            unsigned int encrypted_block =
                    (message_xored_with_gamma >> 1) | ((message_xored_with_gamma << 7) & 0xFF);
            char r1 = encrypted_block;
            outputFile.write(&r1, sizeof(r1));
        }
        outputFile.close();

    } else if (mode == "decryption") {

        // Режим расшифрования
        std::cout << "Input key:";
        int key;
        std::cin >> key;
        /*
        std::ifstream readFile;
        readFile.open(file_name, std::ios::binary);
        std::vector<char> encryptedData((std::istreambuf_iterator<char>(readFile)),
                                        std::istreambuf_iterator<char>());
        readFile.close();
        std::vector<char> decryptedData(encryptedData.size());
        for (int i = 0; i < encryptedData.size(); i += 2) {
            unsigned int gamma = rand();
            unsigned int shifted_encrypted_block = ((encryptedData[i] << 1) & 0xFF) | (encryptedData[i] >> 7);
            unsigned int result = shifted_encrypted_block ^ gamma;
            decryptedData[i] = result;
        }
        */
        srand(key);
        std::ifstream readFile;
        readFile.open(file_name, std::ios::binary);

        std::vector<char> encryptedData((std::istreambuf_iterator<char>(readFile)),
                                        std::istreambuf_iterator<char>());
        readFile.close();

        std::vector<char> decryptedData(encryptedData.size());

        for (int i = 0; i < encryptedData.size(); ++i) {
            unsigned int gamma = rand();
            unsigned char b1 = encryptedData[i];

            unsigned int encrypted_block = (static_cast<unsigned int>(b1));

            unsigned int shifted_encrypted_block =
                    ((encrypted_block << 1) & 0xFF) | (encrypted_block >> 7);
            unsigned char decr = shifted_encrypted_block ^ gamma;
            decryptedData[i] = decr;
        }
            for (char i: decryptedData) {
                std::cout << i;
            }
        }
        return 0;
    }
