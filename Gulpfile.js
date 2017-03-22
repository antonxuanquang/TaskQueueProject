var gulp  = require('gulp')
var shell = require('gulp-shell')
var watch = require('gulp-watch')

gulp.task('compile', shell.task([
  'clear',
  'make clean',
  'make all',
  'clear',
  // './TaskQueueProject 5 10',
  // 'sleep 1',
  // 'clear',
  './taskQueue 2 10'
]))

gulp.task('watch', function() {
    gulp.watch('./*.c', ['compile']);
    gulp.watch('./*.h', ['compile']);
});

gulp.task('default' ,function() {
    gulp.watch('./*.c', ['compile']);
    gulp.watch('./*.h', ['compile']);
});
