#! ruby

#if ARGV.length > 0 then
#	puts ARGV[0]
#end

if ARGV.include? "--clean" then
	#puts "Do cleaninng"
	build_dir = File.absolute_path(__FILE__.encode("UTF-8"))
	build_dir = build_dir.chomp(File.basename(build_dir)) + "build"
	if File.directory? build_dir then
		puts "removing #{build_dir} ... "
		a = system "rm -rf #{build_dir}"
		if not a then
			puts "cannot remove it !"
			exit
		end
		#puts a
	else
		puts "#{build_dir} do not exist"
	end
end

py = "fix_setup.py"
action = "install"
if RUBY_PLATFORM =~ /darwin/ then
	puts "Building under MacOSX"
	system "python3 #{py} #{action}"
elsif RUBY_PLATFORM =~ /mingw/ then
	puts "Building under Windows"
	system "python #{py} #{action}"
end
