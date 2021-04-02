Pod::Spec.new do |s|
  s.name             = 'RangersAppLog'
  s.version          = '5.6.7-rc.0'
  s.summary          = 'ByteDance Rangers AppLog.'
  s.description      = 'ByteDance Rangers AppLog SDK.'
  s.homepage         = 'https://github.com/bytedance/RangersAppLog'
  s.license          = { :type => 'MIT', :file => 'LICENSE' }
  s.author           = { 'duanwenbin' => 'duanwenbin@bytedance.com' }
  s.source           = { :git => 'https://github.com/bytedance/RangersAppLog.git', :tag => s.version.to_s }
  
  s.ios.deployment_target = '9.0'
  s.requires_arc = true
  s.static_framework = true
  s.pod_target_xcconfig = {
    'OTHER_LDFLAGS' => '-lObjC',
    'DEFINES_MODULE' => 'YES',
    'EXCLUDED_ARCHS[sdk=iphonesimulator*]' => 'arm64'
  }
  s.user_target_xcconfig = { 
    'EXCLUDED_ARCHS[sdk=iphonesimulator*]' => 'arm64'
  }
  
  s.subspec 'Core' do |bd|
    bd.source_files = 'RangersAppLog/Classes/Core/*.{h,m,c}'
    bd.vendored_library = 'RangersAppLog/Classes/Core/*.a'
    bd.frameworks = 'UIKit','Foundation','Security','AdSupport','CoreTelephony','CoreFoundation','SystemConfiguration','CoreGraphics'
    bd.library = 'z','sqlite3'
    bd.public_header_files = 'RangersAppLog/Classes/Core/*.h'
  end

  s.subspec 'Host' do |bd|
    bd.dependency 'RangersAppLog/Core'
    bd.subspec 'CN' do |cn|
      cn.source_files = 'RangersAppLog/Classes/Host/CN/*.{h,m,c}'
      cn.public_header_files = 'RangersAppLog/Classes/Host/CN/*.h'
      cn.vendored_library = 'RangersAppLog/Classes/Host/CN/*.a'
    end
    bd.subspec 'SG' do |sg|
      sg.source_files = 'RangersAppLog/Classes/Host/SG/*.{h,m,c}'
      sg.public_header_files = 'RangersAppLog/Classes/Host/SG/*.h'
      sg.vendored_library = 'RangersAppLog/Classes/Host/SG/*.a'
    end
    bd.subspec 'VA' do |va|
      va.source_files = 'RangersAppLog/Classes/Host/VA/*.{h,m,c}'
      va.public_header_files = 'RangersAppLog/Classes/Host/VA/*.h'
      va.vendored_library = 'RangersAppLog/Classes/Host/VA/*.a'
    end
  end

  s.subspec 'Log' do |bd|
    bd.vendored_library = 'RangersAppLog/Classes/Log/*.a'
    bd.dependency 'RangersAppLog/Core'
  end

  s.subspec 'Unique' do |bd|
    bd.frameworks = 'AdSupport' #, 'AppTrackingTransparency'
    bd.dependency 'RangersAppLog/Core'
    bd.source_files = 'RangersAppLog/Classes/Unique/*.{h,m,c}'
    bd.public_header_files = 'RangersAppLog/Classes/Unique/*.h'
    bd.vendored_library = 'RangersAppLog/Classes/Unique/*.a'
  end

  s.subspec 'CAID' do |ss|
    ss.vendored_library = 'RangersAppLog/Classes/CAID/*.a'
    ss.dependency 'RangersAppLog/Core'
  end
  
  s.subspec 'UITracker' do |bd|
    bd.vendored_library = 'RangersAppLog/Classes/UITracker/*.a'
    bd.source_files = 'RangersAppLog/Classes/UITracker/*.{h,m,c}'
    bd.frameworks = 'Foundation','UIKit','WebKit'
    bd.public_header_files = 'RangersAppLog/Classes/UITracker/*.h'
    bd.dependency 'RangersAppLog/Core'
  end

  s.subspec 'Picker' do |bd|
    bd.vendored_library = 'RangersAppLog/Classes/Picker/*.a'
    bd.frameworks = 'Foundation','UIKit','WebKit','CoreText'
    bd.dependency 'RangersAppLog/Log'
    bd.dependency 'RangersAppLog/UITracker'
    bd.source_files = 'RangersAppLog/Classes/Picker/*.{h,m,c}'
    bd.public_header_files = 'RangersAppLog/Classes/Picker/*.h'
  end

end
