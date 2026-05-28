#include <cstdio>
#include <cstdint>
#include <vector>

class FastInput {
    static const int BUFSIZE = 1 << 16;
    char buffer[BUFSIZE];
    int pos = 0, len = 0;

    inline char getChar() {
        if (pos == len) {
            len = (int)std::fread(buffer, 1, BUFSIZE, stdin);
            pos = 0;
            if (len == 0) return 0;
        }
        return buffer[pos++];
    }

public:
    uint32_t readUInt() {
        char c;
        do {
            c = getChar();
        } while (c <= ' ' && c);

        uint32_t x = 0;
        while (c > ' ') {
            x = x * 10u + (uint32_t)(c - '0');
            c = getChar();
        }
        return x;
    }

    uint32_t readIntBits() {
        char c;
        do {
            c = getChar();
        } while (c <= ' ' && c);

        bool neg = false;
        if (c == '-') {
            neg = true;
            c = getChar();
        }

        uint32_t x = 0;
        while (c > ' ') {
            x = x * 10u + (uint32_t)(c - '0');
            c = getChar();
        }
        return neg ? (0u - x) : x;
    }
};

class FastOutput {
    static const int BUFSIZE = 1 << 16;
    char buffer[BUFSIZE];
    int pos = 0;

    inline void putChar(char c) {
        if (pos == BUFSIZE) flush();
        buffer[pos++] = c;
    }

public:
    ~FastOutput() {
        flush();
    }

    void flush() {
        if (pos) {
            std::fwrite(buffer, 1, pos, stdout);
            pos = 0;
        }
    }

    void writeUInt(uint32_t x) {
        char s[10];
        int n = 0;
        do {
            s[n++] = (char)('0' + x % 10u);
            x /= 10u;
        } while (x);
        while (n--) putChar(s[n]);
        putChar('\n');
    }

    void writeIntBits(uint32_t bits) {
        if (bits & 0x80000000u) {
            putChar('-');
            writeUInt((~bits) + 1u);
        } else {
            writeUInt(bits);
        }
    }
};

int main() {
    FastInput in;
    const uint32_t n = in.readUInt();

    std::vector<uint32_t> a(n), b(n);
    uint32_t cnt[4][256] = {};

    for (uint32_t i = 0; i < n; ++i) {
        const uint32_t key = in.readIntBits() ^ 0x80000000u;
        a[i] = key;
        ++cnt[0][key & 255u];
        ++cnt[1][(key >> 8) & 255u];
        ++cnt[2][(key >> 16) & 255u];
        ++cnt[3][key >> 24];
    }

    uint32_t *src = a.data();
    uint32_t *dst = b.data();

    for (int pass = 0; pass < 4; ++pass) {
        uint32_t pos[256];
        uint32_t sum = 0;
        for (int i = 0; i < 256; ++i) {
            pos[i] = sum;
            sum += cnt[pass][i];
        }

        const int shift = pass * 8;
        for (uint32_t i = 0; i < n; ++i) {
            const uint32_t x = src[i];
            dst[pos[(x >> shift) & 255u]++] = x;
        }

        uint32_t *tmp = src;
        src = dst;
        dst = tmp;
    }

    FastOutput out;
    out.writeUInt(n);
    for (uint32_t i = 0; i < n; ++i) {
        out.writeIntBits(src[i] ^ 0x80000000u);
    }

    return 0;
}