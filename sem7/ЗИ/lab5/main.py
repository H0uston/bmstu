from OpenSSL import crypto
import sys

if __name__ == '__main__':

    if sys.argv[1] == "-c":
        with open(sys.argv[2], 'rb') as f:
            data = f.read()

        key = crypto.PKey()
        key.generate_key(crypto.TYPE_RSA, 1024)

        with open(sys.argv[3], 'wb') as f:
            f.write(crypto.dump_publickey(crypto.FILETYPE_PEM, key))

        with open(sys.argv[4], 'wb') as f:
            f.write(crypto.dump_privatekey(crypto.FILETYPE_PEM, key))

        with open(sys.argv[4], 'rb') as f:
            private = crypto.load_privatekey(crypto.FILETYPE_PEM, f.read())

        signature = crypto.sign(private, data, "sha256")
        print(f'Created signature: {signature}')

        with open(sys.argv[5], 'wb') as f:
            f.write(signature)

    if sys.argv[1] == "-v":
        with open(sys.argv[2], 'rb') as f:
            data = f.read()

        with open(sys.argv[3], 'rb') as f:
            pub = crypto.load_publickey(crypto.FILETYPE_PEM, f.read())

        with open(sys.argv[4], 'rb') as f:
            private = crypto.load_privatekey(crypto.FILETYPE_PEM, f.read())

        with open(sys.argv[5], 'rb') as f:
            signature = f.read()

        newCert = crypto.X509()
        newCert.set_pubkey(pub)
        # newCert.sign(private, 'sha256')

        try:
            crypto.verify(newCert, signature, data, "sha256")
            print('Signature checking passed ok!')
        except Exception:
            print('Wrong signature!')
