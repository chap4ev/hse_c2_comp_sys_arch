class EncryptedText:
    def __init__(self):
        self._decrypted_text: str | None = None

    def __len__(self):
        return len(self._decrypted_text)

    @property
    def sum_div_length(self) -> float:
        """Частное от деления суммы кодов незашифрованной строки на число символов в этой строке"""
        return sum(map(ord, self._decrypted_text)) / len(self._decrypted_text)
