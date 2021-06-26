using System;
using System.IO;
using System.Numerics;

namespace RSA
{
    public class RSA
    {
        private const int START_PRIME = 100;
        private const int END_PRIME = 1000;

        private readonly int _p;
        private readonly int _q;
        private readonly int _fi;
        private readonly int _n;
        static Random r = new Random(1);

        public int openExp { get; set; }
        public int secretExp { get; set; }

        public RSA()
        {
            _p = GetRandomPrime();
            _q = GetRandomPrime();
            _fi = (_p - 1) * (_q - 1);
            _n = _p * _q;

            openExp = GetOpenExp(_fi);
            secretExp = GetSecretExp(openExp, _fi);

            //Console.WriteLine($"Params: p={_p} q={_q} n={_n} phi={_fi} opene={openExp} secret={secretExp}\n");
        }

        public int Encrypt(int m)
        {
            return (int)BigInteger.ModPow(m, openExp, _n);
        }

        public int Decrypt(int c)
        {
            return (int)BigInteger.ModPow(c, secretExp, _n);
        }

        private int GetRandomPrime()
        {
            int num = r.Next(START_PRIME, END_PRIME);

            while (!isPrime(num))
            {
                num = r.Next(START_PRIME, END_PRIME);
            }

            return num;
        }

        private bool isPrime(int number)
        {
            if (number == 1) return false;
            if (number == 2) return true;

            var limit = Math.Ceiling(Math.Sqrt(number));

            for (int i = 2; i <= limit; ++i)
                if (number % i == 0)
                    return false;
            return true;

        }

        private int GetOpenExp(int fi)
        {
            int nod = 0;
            int num = -1;

            while (nod != 1)
            {
                num = r.Next(2, fi);
                nod = GCD(fi, num);
            }

            return num;
        }

        private int GetSecretExp(int openExp, int fi)
        {
            int d, k;
            GCDNext(openExp, fi, out d, out k);
            return d;
        }

        private void GCDNext(int a, int b, out int x, out int y)
        {
            if (b == 0)
            {
                x = 1;
                y = 0;

                return;
            }
            //ax + by = nod
            // (d * e) % phi == 1
            // e * d = phi * k + 1
            // 
            GCDNext(b, a % b, out x, out y);

            int tmp = y;
            y = x - (a / b) * (y);
            x = tmp;
        }

        private int GCD(int a, int b)
        {
            return b == 0 ? a : GCD(b, a % b);
        } 
    }

    class Program
    {
        static void EncryptFile(string src, string dst, RSA rsa)
        {
            FileStream fsSrc = new FileStream(src, FileMode.Open);
            FileStream fsDst = new FileStream(dst, FileMode.Create);

            BinaryWriter binWriter = new BinaryWriter(fsDst);
            int cur;
            while (fsSrc.CanRead)
            {
                cur = fsSrc.ReadByte();
                if (cur == -1)
                    break;
                int res = rsa.Encrypt(cur);
                binWriter.Write(res);
            }
            binWriter.Write(-1);
            binWriter.Close();
            fsDst.Close();
            fsSrc.Close();
        }

        static void DecryptFile(string src, string dst, RSA rsa)
        {
            FileStream fsSrc = new FileStream(src, FileMode.Open);
            FileStream fsDst = new FileStream(dst, FileMode.Create);
            BinaryReader binReader = new BinaryReader(fsSrc);

            int cur;
            while (fsSrc.CanRead)
            {
                cur = binReader.ReadInt32();
                if (cur == -1)
                    break;
                int res = rsa.Decrypt(cur);
                fsDst.WriteByte((byte)res);
            }

            binReader.Close();
            fsDst.Close();
            fsSrc.Close();
        }

        static void Main(string[] args)
        {
            Console.WriteLine("Start!");
            RSA rsa = new RSA();

            string firstFile = args[1];
            string secondFile = args[2];
            if (args[0] == "e")
            {
                string keyPath = args[3];
                TextReader reader = File.OpenText(keyPath);
                rsa.openExp = int.Parse(reader.ReadLine());
                EncryptFile(firstFile, secondFile, rsa);
            }
            else if (args[0] == "k")
            {
                var publicKeyFile = new StreamWriter(firstFile);
                publicKeyFile.WriteLine(rsa.openExp.ToString());
                publicKeyFile.Close();
                var privateKeyFile = new StreamWriter(secondFile);
                privateKeyFile.WriteLine(rsa.secretExp.ToString());
                privateKeyFile.Close();
            }
            else if (args[0] == "d")
            {
                string keyPath = args[3];
                TextReader reader = File.OpenText(keyPath);
                rsa.secretExp = int.Parse(reader.ReadLine());
                
                DecryptFile(firstFile, secondFile, rsa);
            }
            else
            {
                Console.WriteLine("Wrong arg");
                return;
            }

            Console.WriteLine("End!");
        }
    }
}
