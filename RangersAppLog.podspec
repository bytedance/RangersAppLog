Pod::Spec.new do |s|
  s.name             = 'RangersAppLog'
  s.version          = '3.2.7-rc.0'
  s.summary          = 'ByteDance Rangers AppLog.'
  s.description      = 'ByteDance Rangers AppLog SDK.'
  s.homepage         = 'https://github.com/bytedance/RangersAppLog'
  s.license          = { :type => 'MIT', :file => 'LICENSE' }
  s.author           = { 'duanwenbin' => 'duanwenbin@bytedance.com' }
  s.source           = { :git => 'https://github.com/bytedance/RangersAppLog.git', :tag => s.version.to_s }

  s.ios.deployment_target = '8.0'
  s.requires_arc = true
  s.static_framework = true
  s.default_subspec = 'UITracker'
  s.pod_target_xcconfig = { 'OTHER_LDFLAGS' => '-lObjC' }

  s.subspec 'Core' do |core|
        core.source_files = 'RangersAppLog/Core/*.h'
        core.vendored_library = 'RangersAppLog/Core/*.a'
        core.frameworks = 'Foundation','Security','AdSupport','CoreTelephony','CoreFoundation','SystemConfiguration'
        core.library = 'z','sqlite3'
        core.public_header_files = 'RangersAppLog/Core/*.h'
  end

  s.subspec 'UITracker' do |tracker|
        tracker.vendored_library = 'RangersAppLog/UITracker/*.a'
        tracker.source_files = 'RangersAppLog/UITracker/*.h'
        tracker.frameworks = 'UIKit','WebKit'
        tracker.public_header_files = 'RangersAppLog/UITracker/*.h'
        tracker.dependency 'RangersAppLog/Core'
  end

   s.subspec 'Picker' do |picker|
        picker.vendored_library = 'RangersAppLog/Picker/*.a'
        picker.source_files = 'RangersAppLog/Picker/*.h'
        picker.frameworks = 'CoreGraphics','CoreServices','MobileCoreServices','QuartzCore','CoreText'
        picker.dependency 'RangersAppLog/UITracker'
        picker.public_header_files = 'RangersAppLog/Picker/*.h'
        picker.resource_bundles = {
          'RangersAppLog' => ['RangersAppLog/Assets/*.xcassets']
        }
  end

end
