import random
import re
import string
import sys

from src.text_encryption.encrypted_text import EncryptedText


class CycleEncryption(EncryptedText):
    def __init__(self):
        super().__init__()
        self._encrypted_text: str | None = None
        self._shift: int | None = None

    def __repr__(self):
        return f"[Cycle encryption:\n" \
               f"\tencrypted_text: {self._encrypted_text}\n" \
               f"\tdecrypted_text: {self._decrypted_text}\n" \
               f"\tshift: {self._shift}\n" \
               f"\tsum_div_length: {self.sum_div_length}]"

    def random_fill(self):
        self._shift = random.randint(-100, 101)

        chars = string.digits + string.ascii_letters + " "

        str_len = random.randint(1, 100)
        self._decrypted_text = "".join(random.choice(chars) for _ in range(str_len))
        self._encrypted_text = "".join(chr((ord(char) + self._shift) % 128) for char in self._decrypted_text)
        return self

    def decrypt(self):
        self._decrypted_text = "".join(
            chr((ord(char) - self._shift + 128) % 128) for char in self._encrypted_text
        )

    def fill_from_str(self, input_str: str):
        shift, self._encrypted_text = input_str.split(' ', 1)
        self._shift = int(shift)
        self.decrypt()
        return self
