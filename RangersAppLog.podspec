Pod::Spec.new do |s|
  s.name             = 'RangersAppLog'
  s.version          = '5.5.0'
  s.summary          = 'ByteDance Rangers AppLog.'
  s.description      = 'ByteDance Rangers AppLog SDK.'
  s.homepage         = 'https://github.com/bytedance/RangersAppLog'
  s.license          = { :type => 'MIT', :file => 'LICENSE' }
  s.author           = { 'duanwenbin' => 'duanwenbin@bytedance.com' }
  s.source           = { :git => 'https://github.com/bytedance/RangersAppLog.git', :tag => s.version.to_s }

  s.ios.deployment_target = '8.0'
  s.requires_arc = true
  s.static_framework = true
  s.pod_target_xcconfig = {
    'OTHER_LDFLAGS' => '-lObjC',
    'DEFINES_MODULE' => 'YES',
  }

  s.subspec 'Core' do |bd|
    bd.source_files = 'RangersAppLog/Core/*.{h,m,c}'
    bd.vendored_library = 'RangersAppLog/Core/*.a'
    bd.frameworks = 'UIKit','Foundation','Security','AdSupport','CoreTelephony','CoreFoundation','SystemConfiguration','CoreGraphics'
    bd.library = 'z','sqlite3'
    bd.public_header_files = 'RangersAppLog/Core/*.h'
  end

  s.subspec 'Host' do |bd|
    bd.dependency 'RangersAppLog/Core'
    bd.subspec 'CN' do |cn|
      cn.source_files = 'RangersAppLog/Host_CN/*.{h,m,c}'
      cn.public_header_files = 'RangersAppLog/Host_CN/*.h'
      cn.vendored_library = 'RangersAppLog/Host_CN/*.a'
    end
    bd.subspec 'SG' do |sg|
      sg.source_files = 'RangersAppLog/Host_SG/*.{h,m,c}'
      sg.public_header_files = 'RangersAppLog/Host_SG/*.h'
      sg.vendored_library = 'RangersAppLog/Host_SG/*.a'
    end
    bd.subspec 'VA' do |va|
      va.source_files = 'RangersAppLog/Host_VA/*.{h,m,c}'
      va.public_header_files = 'RangersAppLog/Host_VA/*.h'
      va.vendored_library = 'RangersAppLog/Host_VA/*.a'
    end
  end

  s.subspec 'Log' do |bd|
    bd.vendored_library = 'RangersAppLog/Log/*.a'
    bd.dependency 'RangersAppLog/Core'
  end

  s.subspec 'Unique' do |bd|
    bd.frameworks = 'AdSupport'
    bd.dependency 'RangersAppLog/Core'
    bd.source_files = 'RangersAppLog/Unique/*.{h,m,c}'
    bd.public_header_files = 'RangersAppLog/Unique/*.h'
    bd.vendored_library = 'RangersAppLog/Unique/*.a'
  end

  s.subspec 'UITracker' do |bd|
    bd.vendored_library = 'RangersAppLog/UITracker/*.a'
    bd.source_files = 'RangersAppLog/UITracker/*.{h,m,c}'
    bd.frameworks = 'Foundation','UIKit','WebKit'
    bd.public_header_files = 'RangersAppLog/UITracker/*.h'
    bd.dependency 'RangersAppLog/Core'
  end

  s.subspec 'Picker' do |bd|
    bd.vendored_library = 'RangersAppLog/Picker/*.a'
    bd.frameworks = 'Foundation','UIKit','WebKit','CoreText'
    bd.dependency 'RangersAppLog/Log'
    bd.dependency 'RangersAppLog/UITracker'
    bd.source_files = 'RangersAppLog/Picker/*.{h,m,c}'
    bd.public_header_files = 'RangersAppLog/Picker/*.h'
    bd.resource_bundles = {
      'RangersAppLog' => ['RangersAppLog/Assets/*.xcassets']
    }
  end

end
