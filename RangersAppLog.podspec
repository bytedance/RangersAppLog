Pod::Spec.new do |s|
  s.name             = 'RangersAppLog'
  s.version          = '4.5.0'
  s.summary          = 'ByteDance Rangers AppLog.'
  s.description      = 'ByteDance Rangers AppLog SDK.'
  s.homepage         = 'https://github.com/bytedance/RangersAppLog'
  s.license          = { :type => 'MIT', :file => 'LICENSE' }
  s.author           = { 'duanwenbin' => 'duanwenbin@bytedance.com' }
  s.source           = { :git => 'https://github.com/bytedance/RangersAppLog.git', :tag => s.version.to_s }

  s.ios.deployment_target = '8.0'
  s.requires_arc = true
  s.static_framework = true
  s.source_files = 'RangersAppLog/*.{h,m}'
  s.pod_target_xcconfig = {
    'OTHER_LDFLAGS' => '-lObjC',
    'DEFINES_MODULE' => 'YES',
  }

  s.subspec 'Core' do |bd|
    bd.source_files = 'RangersAppLog/Core/*.h'
    bd.vendored_library = 'RangersAppLog/Core/*.a'
    bd.frameworks = 'Foundation','Security','AdSupport','CoreTelephony','CoreFoundation','SystemConfiguration'
    bd.library = 'z','sqlite3'
    bd.public_header_files = 'RangersAppLog/Core/*.h'
  end

  s.subspec 'UITracker' do |bd|
    bd.vendored_library = 'RangersAppLog/UITracker/*.a'
    bd.source_files = 'RangersAppLog/UITracker/*.h'
    bd.frameworks = 'UIKit','WebKit'
    bd.public_header_files = 'RangersAppLog/UITracker/*.h'
    bd.dependency 'RangersAppLog/Core'
  end

  s.subspec 'Picker' do |bd|
    bd.vendored_library = 'RangersAppLog/Picker/*.a'
    bd.frameworks = 'CoreGraphics','CoreServices','MobileCoreServices','QuartzCore','CoreText'
    bd.dependency 'RangersAppLog/UITracker'
    bd.resource_bundles = {
      'RangersAppLog' => ['RangersAppLog/Assets/*.xcassets']
    }
  end

end
