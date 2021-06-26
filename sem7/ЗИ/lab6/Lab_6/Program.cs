using System;
using System.IO;

namespace Lab6
{
    class Program
    {
        static void Main(string[] args)
        {
            var fileToCompress = args[0];
            var fileTestCompress = args[1];
            var fileUncompressed = args[2];

            var lzw = new LZW();
            var testData = File.ReadAllBytes(fileToCompress);

            Console.WriteLine($"Длина исходного: {testData.Length}");

            var compressedData = lzw.Compress(testData);
            Console.WriteLine($"Длина сжатого: {compressedData.Length / 2.0}");

            var uncompressedData = lzw.UnCompress(compressedData);
            Console.WriteLine($"Длина разжатого: {uncompressedData.Length}");

            File.WriteAllBytes(fileTestCompress, compressedData);
            File.WriteAllBytes(fileUncompressed, uncompressedData);
        }
    }
}