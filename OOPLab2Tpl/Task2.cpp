#include <iostream>
#include <bitset>
#include <string>
#include <fstream>

void myFunction() {
	std::cout << "Hello from function 2" << std::endl;
}


// Функція для отримання біта парності
bool getParity(unsigned char value) {
    int count = 0;
    for (int i = 0; i < 8; ++i) {
        if (value & (1 << i))
            count++;
    }
    return count % 2 == 0;
}

// Функція для шифрування тексту
void encryptText(const std::string& text, unsigned short* encryptedData) {
    // Перевірка, чи текст не перевищує максимальну довжину
    if (text.length() > 64) {
        std::cout << "Input text is too long." << std::endl;
        return;
    }

    // Шифрування кожного символу тексту
    for (int i = 0; i < text.length(); ++i) {
        // Отримання позиції символу в рядку
        unsigned short position = i;

        // Отримання ASCII-коду символу
        unsigned short asciiCode = text[i];

        // Визначення бітів парності
        bool positionParity = getParity(position);
        bool asciiParity = getParity(asciiCode);

        // Формування зашифрованого символу
        encryptedData[i] = (position & 0x003F) | (positionParity << 6) | ((asciiCode & 0x007F) << 7) | (asciiParity << 15);
// 0x003F  = 0000 0000 0111 1111
	    
        std::cout << "Encrypted " << i << " successfully. Result is: " << std::bitset<16>(encryptedData[i]) << std::endl;
    }
}

// Функція для дешифрування тексту
void decryptText(const unsigned short* encryptedData, int length) {
    // Ініціалізація масиву для зберігання розшифрованих даних
    char decryptedData[64] = { 0 };

    // Дешифрування кожного символу тексту
    for (int i = 0; i < length; ++i) {
        // Отримання позиції символу в рядку та ASCII-коду символу з зашифрованого символу
        unsigned short position = (encryptedData[i] & 0x003F);
        unsigned short asciiCode = ((encryptedData[i] >> 7) & 0x007F);

        // Визначення бітів парності
        bool positionParity = (encryptedData[i] >> 6) & 1;
        bool asciiParity = (encryptedData[i] >> 15) & 1;

        // Перевірка бітів парності
        if (getParity(position) != positionParity || getParity(asciiCode) != asciiParity) {
            std::cout << "Error: Parity check failed for symbol at position " << i << std::endl;
            continue;
        }

        // Зберігання розшифрованого символу у масиві
        decryptedData[position] = asciiCode;
    }

    // Виведення розшифрованого тексту
    std::cout << "Decrypted Text: " << decryptedData << std::endl;

    // Відкриваємо файл для запису
    std::ofstream outFile("decrypted.txt");

    // Записуємо елементи масиву у файл
    for (int i = 0; i < 64; ++i) {
        outFile << decryptedData[i];
    }

    // Закриваємо файл
    outFile.close();

    std::cout << "Sucsessfuly write to 'decrypted.txt'." << std::endl;
}

void Task2() {
    std::string inputText;
    std::cout << "Enter text (up to 64 characters): ";
    std::cin >> inputText;

    // Доповнення тексту пробілами до 64 символів
    inputText.resize(64, ' ');

    // Ініціалізація масиву для зберігання зашифрованих даних
    unsigned short encryptedData[64] = { 0 };

    std::cout << "Encrypted Data:" << std::endl;
    encryptText(inputText, encryptedData);

    std::ofstream outputb("encrypted.bin", std::ios::out | std::ios::binary); // Відкриваємо файл для запису результату
    outputb.write((char*)encryptedData, 64 * sizeof(unsigned short)); // Записуємо результат у файл
    outputb.close(); // Закриваємо файл

    std::ifstream inputb("encrypted.bin", std::ios::binary); // Відкриваємо файл для читання зашифрованих даних

    unsigned short* encodedDataFromFile = new unsigned short[64]; // Виділяємо пам'ять під масив для зашифрованих даних
    inputb.read((char*)encodedDataFromFile, 64 * sizeof(unsigned short)); // Читаємо зашифровані дані з файлу
    inputb.close(); // Закриваємо файл

    // Виклик функції для дешифрування тексту та виведення розшифрованого тексту
    decryptText(encodedDataFromFile, inputText.length());
}
