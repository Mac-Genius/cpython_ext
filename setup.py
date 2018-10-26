import setuptools

with open("README.md", "r") as fh:
    long_description = fh.read()

cpython_module = setuptools.Extension('_cpython', sources=['cpython/cpython.c'],
                                      include_dirs=['/usr/include'])

setuptools.setup(
    name="cpython",
    version="0.0.1",
    author="John Harrison",
    author_email="jwharrison007@gmail.com",
    description="A test.",
    long_description=long_description,
    long_description_content_type="text/markdown",
    packages=setuptools.find_packages(),
    classifiers=[
        "Programming Language :: Python :: 3",
        "License :: OSI Approved :: MIT License",
    ],
    entry_points={
        'console_scripts': []
    },
    ext_modules=[cpython_module]
)
