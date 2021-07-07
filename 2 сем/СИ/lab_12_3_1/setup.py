# python3
# encoding: utf-8

from distutils.core import setup, Extension

module = Extension('function', sources = ['function.c'])

setup(name='function',
	version='1.1.2',
	description='Function for lab',
	ext_modules=[module])
