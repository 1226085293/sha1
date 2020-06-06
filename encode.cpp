void sha1(std::string& data_) {
  // 计算占用空间
  uint32_t size, i, n;
  uint32_t len = static_cast<uint32_t>(data_.length());
  uint32_t rem = len % 64;
  if (rem < 56) {
    size = len - rem + 64;
  }
  else if (rem == 56) {
    size = len + 8 + 64;
  }
  else {
    size = len + 64 - rem + 64;
  }
  uint32_t* output = new uint32_t[size / 4]{};
  for (i = 0; i < len; i++) {
    output[i / 4] |= data_[i] << (24 - ((i & 0x03) << 3));
  }
  n = 24 - ((i & 0x03) << 3);
  // 补位
  output[i / 4] |= 0x80 << n;
  // 补长
  output[size / 4 - 1] = len * 8;
  // 计算消息摘要
  uint32_t j;
  uint32_t buf[5];
  uint32_t w[80];
  uint32_t k[] = { 0x5A827999, 0x6ED9EBA1, 0x8F1BBCDC, 0xCA62C1D6 };
  uint32_t h[] = { 0x67452301, 0xEFCDAB89, 0x98BADCFE, 0x10325476, 0xC3D2E1F0 };
  uint32_t index, temp1, temp2;
  for (i = 0; i < size / 4; i += 16) {
    for (j = 0; j < 16; ++j) {
      w[j] = output[j + i];
    }
    for (j = 16; j < 80; ++j) {
      w[j] = w[j - 3] ^ w[j - 8] ^ w[j - 14] ^ w[j - 16];
      w[j] = (w[j] << 1) | (w[j] >> 31);
    }
    for (j = 0; j < 5; ++j) {
      buf[j] = h[j];
    }
    for (j = 0; j < 80; ++j) {
      index = j / 20;
      temp1 = index == 0 ? ((buf[1] & buf[2]) | (~buf[1] & buf[3])) :
        (index == 1 ? (buf[1] ^ buf[2] ^ buf[3]) :
          (index == 2 ? ((buf[1] & buf[2]) | (buf[1] & buf[3]) | (buf[2] & buf[3])) :
            (buf[1] ^ buf[2] ^ buf[3])));
      temp2 = ((buf[0] << 5) | (buf[0] >> 27)) + temp1 + buf[4] + w[j] + k[index];
      buf[4] = buf[3];
      buf[3] = buf[2];
      buf[2] = (buf[1] << 30) | (buf[1] >> 2);
      buf[1] = buf[0];
      buf[0] = temp2;
    }
    for (j = 0; j < 5; ++j) {
      h[j] += buf[j];
    }
  }
  delete[] output;
  data_.resize(20);
  for (i = 0; i < 20; ++i) {
    data_[i] = reinterpret_cast<char*>(h + i/4)[(19-i) & 0x03];
  }
  //printf("SHA1 = %08X%08X%08X%08X%08X\n",h[0],h[1],h[2],h[3],h[4]);
}
