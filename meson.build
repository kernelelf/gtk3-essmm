project('gtk3-essmm', 'c',
  version : '0.1',
  default_options : ['warning_level=3'])


cc = meson.get_compiler('c')

gtk3_lib = cc.find_library('gtk-3',required: false)
gtk3_dep = dependency('gtk+-3.0')

src = [
  'main.c'

]

c_ex = ['-I""']


executable('gtk3-essmm',
           src,
		   c_args: c_ex,
		   dependencies: [gtk3_dep,gtk3_lib],
           install : true)
