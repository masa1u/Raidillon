from setuptools import setup, Extension
import os

# pybind11のインクルードディレクトリを手動で指定
pybind11_include = os.path.abspath(os.path.join(os.path.dirname(__file__), 'pybind11/include'))

# ビルドディレクトリのパスを取得
build_dir = os.path.abspath(os.path.join(os.path.dirname(__file__), '../../build'))

# モジュールの定義
ext_modules = [
    Extension(
        'raidillon_bindings',
        sources=[os.path.abspath(os.path.join(os.path.dirname(__file__), 'raidillon_bindings.cc'))],
        include_dirs=[
            pybind11_include,
            os.path.abspath(os.path.join(os.path.dirname(__file__), '../../include'))
        ],
        library_dirs=[os.path.join(build_dir, 'src')],
        libraries=['Raidillon'],
        language='c++',
        extra_compile_args=['-std=c++17'],  
    ),
]

setup(
    name='raidillon_bindings',
    version='0.1',
    author='Masaru Uchida',
    description='Python bindings for Raidillon',
    ext_modules=ext_modules,
    install_requires=['pybind11'],
    zip_safe=False,
)